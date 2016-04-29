local socketTcp = require('app.views.SocketTCP')
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

require("app.views.addressbook_pb.lua")
require('app.core.LuaCustomEvent')
local updater = require('app.updater.updater')

MainScene.RESOURCE_FILENAME = "MainScene.csb"

function MainScene:onCreate()
    printf("resource node = %s", tostring(self:getResourceNode()))
    
    --[[ you can create scene with following comment code instead of using csb file.
    -- add background image
    display.newSprite("HelloWorld.png")
        :move(display.center)
        :addTo(self)

    -- add HelloWorld label
    cc.Label:createWithSystemFont("Hello World", "Arial", 40)
        :move(display.cx, display.cy + 200)
        :addTo(self)
    ]]
    self.proto = ccluaext.BinaryStream:create(1024)
    self.proto:writeInt(100)
    print(self.proto:readInt())

    local tmp = self.proto:getTotalBuff()
    self.proto:setBuff(tmp)
    print(self.proto:readInt())
    self.proto:retain()
    --[[
    getmetatable(self.proto).__gc = function ()
        self.proto:release()
        print("=======================")
    end
    --]]
    print(getmetatable(self.proto).__gc)

  
    --local uphelper = ccluaext.UpdaterHelper:getInstance()
    --local localpath = cc.FileUtils:getInstance():getWritablePath() .. 'tmp/'
    --uphelper:downloadFile('http://127.0.0.1:8000/main.lua', localpath .. 'main.lua', 'main.lua')
    updater.checkHasUpdate('', function (hasUpdate)
        print('=================checkupdatecallback===================')
        print(hasUpdate)
        if hasUpdate then
            updater.startUpdate()
        end
    end)

    collectgarbage() 
    local function onConnected(event)
        self.isconnect = true
        --self.mysocket:send('test it')
    end
    local function onData(__event)
         print("socket status: %s, partial:%s", __event.name, __event.data)
         local data = __event.data
         --[[
         setbuff(data)
         print(readint())
         print(readint())
         print(readstring())
         print(readstring())
         --]]
         print("-------------------------")
        local operson = addressbook_pb.Person()
        operson:ParseFromString(data)

        print(operson.name)
        print(operson.id)
        print(operson.email)
        for _, phone in ipairs(operson.phone) do
            print(phone.number)
            print(phone.type)
        end
    end
    self.isconnect = false
    self.mysocket = socketTcp.new('127.0.0.1', 17643)
    self.mysocket:addEventListener(socketTcp.EVENT_CONNECTED, onConnected)
    self.mysocket:addEventListener(socketTcp.EVENT_DATA, onData)


    local function connect()
        self.mysocket:connect()
    end
    local connectItem = cc.MenuItemFont:create("connect")
    connectItem:registerScriptTapHandler(connect)

    local function sendMSG()
        --self.proto:release()
        --[[
        self.proto = nil
        resetbuff()
        addint(3)
        addint(5)
        addstring("first")
        addstring("second")
        local str = gettotalbuff()
        self.mysocket:send(str)
        --]]
        --encode
        local myperson = addressbook_pb.Person()
        myperson.name = "name"
        myperson.id = 123456
        myperson.email = "tt@tmp.com"
        for i = 1, 3 do 
            local phone1 = myperson.phone:add() --addressbook_pb.Person.PhoneNumber()
            phone1.number = "128822444121"
            phone1.type = addressbook_pb.Person.MOBILE
        end
        --myperson:set_phone(1, phone1)

        local str = myperson:SerializeToString()
        local file = io.open('testproto.txt', 'wb')
        file:write(str)
        file:close()
        self.mysocket:send(str)
        print(string.len(str))
        print(str)
        --decode
        local operson = addressbook_pb.Person()
        operson:ParseFromString(str)

        print(operson.name)
        print(operson.id)
        print(operson.email)
        for _, phone in ipairs(operson.phone) do
            print(phone.number)
            print(phone.type)
        end

        print('lua int to binary string-------------')
        local a = 1953855090
    end
    local sendItem = cc.MenuItemFont:create("sendMSG")
    sendItem:registerScriptTapHandler(sendMSG)

    local menu = cc.Menu:create()
    menu:addChild(connectItem)
    menu:addChild(sendItem)
    menu:alignItemsVertically()

    self:addChild(menu)
    local s = cc.Director:getInstance():getWinSize()

    menu:setPosition(cc.p(s.width/2, s.height/2))
--[[
    addstring("first")
    readstring()
    addint(3)
    addint(5)
    print(readint())
    print(readint())

    addint(100)
    print(readint())

    addstring('test string')
    print(readstring())

    local totalstring = gettotalbuff()
    print(totalstring)
    print(string.len(totalstring))

    setbuff(totalstring)
    print(readstring())
    print(readstring())
    --]]
    print("***********************************************")
    local a1, a2, a3, a4 = 1, 2, 4, 5
    local a, n = average(a1, a2, a3, a4)
    print(a1, a2, a3, a4)
    print(a, n)
end

return MainScene
