
--cc.FileUtils:getInstance():setPopupNotify(false)
--cc.FileUtils:getInstance():addSearchPath("src/")
--cc.FileUtils:getInstance():addSearchPath("res/")
--writablepath = cc.FileUtils:getInstance():getWritablePath()
--package.path = './src/?.lua;' .. package.path
--package.path = writablepath .. 'src/?.lua;' .. package.path
debugPrint = true
if debugPrint then
    ---[[
    --use BabeLua to debug
    function babe_tostring(...)
        local num = select("#",...);
        local args = {...};
        local outs = {};
        for i = 1, num do
            if i > 1 then
                outs[#outs+1] = "\t";
            end
            outs[#outs+1] = tostring(args[i]);
        end
        return table.concat(outs);
    end

    local babe_print = print;
    local babe_output = function(...)
        babe_print(...);

        if decoda_output ~= nil then
            local str = babe_tostring(...);
            decoda_output(str);
        end
    end
    print = babe_output;
    --]]
end

--require "config"
--require "cocos.init"
--local function main()
--    local app = require("app.MyApp")
--    local tapp = app:create()
--    tapp:run()
--end

--local status, msg = xpcall(main, __G__TRACKBACK__)
--if not status then
--    print(msg)
--end

cc.FileUtils:getInstance():setPopupNotify(false)
cc.FileUtils:getInstance():addSearchPath("src/")
cc.FileUtils:getInstance():addSearchPath("res/")
writablepath = cc.FileUtils:getInstance():getWritablePath()
package.path = './src/?.lua;' .. package.path
package.path = writablepath .. 'src/?.lua;' .. package.path
print("123123")
require("app.views.addressbook_pb.lua")
require('app.core.LuaCustomEvent')
local updater = require('app.updater.updater')
--local socketTcp = require('app.views.SocketTCP')

local director = cc.Director:getInstance()
local view = director:getOpenGLView()

if not view then
    local width = 1736
    local height = 640
    view = cc.GLViewImpl:createWithRect("Cocos2d-Lua", cc.rect(0, 0, width, height))
    director:setOpenGLView(view)
end

local framesize = view:getFrameSize()
local textureCache = director:getTextureCache()
local spriteFrameCache = cc.SpriteFrameCache:getInstance()
local animationCache = cc.AnimationCache:getInstance()

view:setDesignResolutionSize(1136, 640, 1)
local scene = cc.Scene:create()

local layer = cc.Layer:create()
local self = layer
scene:addChild(layer)

local winSize = director:getWinSize()
local center = {x = winSize.width * 0.5, y = winSize.height * 0.5}

local sprite = cc.Sprite:create("HelloWorld.png")
sprite:setPosition(center)
layer:addChild(sprite)

    -- add HelloWorld label
local label = cc.Label:createWithSystemFont("Hello World", "Arial", 40)
label:setPosition(center.x, center.y + 200)
layer:addChild(label)

director:runWithScene(scene)



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
--self.mysocket = socketTcp.new('127.0.0.1', 17643)
--self.mysocket:addEventListener(socketTcp.EVENT_CONNECTED, onConnected)
--self.mysocket:addEventListener(socketTcp.EVENT_DATA, onData)


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
    myperson.id = "-3543488481790448384"
    myperson.email = "tt@tmp.com"
    myperson.tint32 = 32;
	myperson.tint64 = "-640000000000000000";
	myperson.tuint32 = 32;
	myperson.tuint64 = "640000000000000000";
	myperson.tsint32 = -32;
	myperson.tsint64 = "-640000000000000000";
	myperson.tbool = false;
	myperson.tfixed64 = "640000000000000000";
	myperson.tsfixed64 = "-640000000000000000";
	myperson.tdouble = 1.234092384;
	myperson.tfixed32 = 32;
	myperson.tsfixed32 = -32;
	myperson.tfloat = 1.25;

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
    --self.mysocket:send(str)
    print(string.len(str))
    print(str)
    --decode
    local operson = addressbook_pb.Person()
    operson:ParseFromString(str)

    print(operson.name)
    print(operson.id)
    print(operson.email)
    print(operson.tint32);
	print(operson.tint64);
	print(operson.tuint32);
	print(operson.tuint64);
	print(operson.tsint32);
	print(operson.tsint64);
	print(operson.tbool);
	print(operson.tfixed64);
	print(operson.tsfixed64);
	print(operson.tdouble);
	print(operson.tfixed32);
	print(operson.tsfixed32);
	print(operson.tfloat);

    for k, v in pairs(operson) do
        print(k, v)
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

menu:setPosition(center)
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

a = 17592186044415
print(a)
a = 0xFFFFFFFFFF
print(a)
print(a * 20 * 1000 * 1000)