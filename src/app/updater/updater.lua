local luaCustomEvent = require('app.core.LuaCustomEvent')
local updater = {}
local lfs = require('lfs')
function updater.clone(object)
    local lookup_table = {}
    local function _copy(object)
        if type(object) ~= "table" then
            return object
        elseif lookup_table[object] then
            return lookup_table[object]
        end
        local new_table = {}
        lookup_table[object] = new_table
        for key, value in pairs(object) do
            new_table[_copy(key)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(object))
    end
    return _copy(object)
end

local fileutils = cc.FileUtils:getInstance() 
function updater.readFile(path)
    return fileutils:getDataFromFile(path)
end

function updater.isFileExists(path)
    return fileutils:isFileExist(path)
end

function updater.isDirExists(path)
    return fileutils:isDirectoryExist(path)
end

function updater.mkdir(path)
    if not updater.isDirExists(path) then
        return lfs.mkdir(path)
    end
    return true
end

function updater.rmdir(path)
    print("updater.rmdir:", path)
    local ret, des = lfs.rmdir(path)
    if updater.isDirExists(path) then
        print('do rm dir=============')
        local function _rmdir(path)
            local iter, dir_obj = lfs.dir(path)
            while true do
                local dir = iter(dir_obj)
                if dir == nil then break end
                if dir ~= "." and dir ~= ".." then
                    local curDir = path..dir
                    local mode = lfs.attributes(curDir, "mode") 
                    if mode == "directory" then
                        _rmdir(curDir.."/")
                    elseif mode == "file" then
                        os.remove(curDir)
                    end
                end
            end
            local succ, des = lfs.rmdir(path)--os.remove(path)
            if des then print(des) end
            return succ
        end
        _rmdir(path)
    end
    return true
end

function updater.writeFile(path, content, mode)
    mode = mode or "wb"
    local file = io.open(path, mode)
    if file then
        if file:write(content) == nil then return false end
        io.close(file)
        return true
    else
        return false
    end
end

local basedir = 'src/app/'
local resinfoFileName = 'resinfo.lua'
local writablePath = fileutils:getWritablePath()
local tmpdir = writablePath .. 'tmp/'

local updateModuleNamePath = ''

local resInfoRelativePath = ''
local uresInfoPath = writablePath .. resInfoRelativePath
local uresInfoTmpPath = tmpdir .. resInfoRelativePath

local resInfoDownloadID = '__DownloadResInfo__'

local updaterHelper = ccluaext.UpdaterHelper:getInstance(6, 8, '.tmp')

--this value must be clear
local localResInfo = nil
local remoteResInfo = nil
local checkUpdateHandler = nil
local updateCompleteHander = nil
local updateProcessHander = nil

local diffResDict = {}
local totalNeedDownloadFiles = 0
local curDownloadFiles = 0
local errorDownloadFiles = 0
local uresInfoDir = nil
updater._dirList = {}

luaCustomEvent.registerEventHandle(9, function (proto)
    print('===============ontaskerror====================')
    local url = proto:readString()
    local storagePath = proto:readString()
    local id = proto:readString()
    if id == resInfoDownloadID then
        updater.onDownloadResinfo(storagePath, false)
    else
        errorDownloadFiles = errorDownloadFiles + 1
        curDownloadFiles = curDownloadFiles + 1
        updater.onOneFileDownload(id, false)
    end
end)

luaCustomEvent.registerEventHandle(10, function (proto)
    print('===============ontaskprocess==================')
    print(proto:readInt())
    print(proto:readInt())
    print(proto:readString())
end)

luaCustomEvent.registerEventHandle(11, function (proto)
    print('===============ontasksuccess==================')
    local url = proto:readString()
    local storagePath = proto:readString()
    local id = proto:readString()
    if id == resInfoDownloadID then
        updater.onDownloadResinfo(storagePath, true)
    else 
        curDownloadFiles = curDownloadFiles + 1
        updater.onOneFileDownload(id, true)
    end
end)

function updater.onDownloadResinfo(path, isok)
    local hasUpdate = false
    if isok then
        remoteResInfo = assert(loadstring(updater.readFile(path)))()
        if remoteResInfo and remoteResInfo.version then
            if not localResInfo then
                hasUpdate = true
            elseif remoteResInfo.version ~= localResInfo.version then
                hasUpdate = true
            end
        end
    end
    checkUpdateHandler(hasUpdate)
end

function updater.setUpdateModuleName(name)
    if string.len(name) > 0 then
        name = name .. '/'
    end
    updateModuleNamePath = name
    resInfoRelativePath = basedir .. updateModuleNamePath .. resinfoFileName
    uresInfoPath = writablePath .. resInfoRelativePath
    uresInfoTmpPath = tmpdir .. resInfoRelativePath
    uresInfoDir = writablePath .. basedir .. updateModuleNamePath
end

local function getLocalResInfo()
    local resInfoTex = nil
    if updater.isFileExists(uresInfoPath) then 
        resInfoTex = updater.readFile(uresInfoPath)
    else 
        resInfoTex = updater.readFile(resInfoRelativePath)
        if resInfoTex then
            updater.mkdir(uresInfoDir)
            updater.writeFile(uresInfoPath, resInfoTex)
        end
    end
    if resInfoTex and string.len(resInfoTex) > 1 then
        return assert(loadstring(resInfoTex))()
    end
    return nil
end

local function downloadResInfo(url)
    updaterHelper:downloadFile(url, uresInfoTmpPath, resInfoDownloadID)
end

local function downloadRes(url, id)
    local realUrl = url .. id
    local storagePath = tmpdir .. id
    updaterHelper:downloadFile(realUrl, storagePath, id)
end

--modulename '' is game lobby. other is gamename.
function updater.checkHasUpdate(modulename, callback)
    updater.setUpdateModuleName(modulename)
    localResInfo = getLocalResInfo()
    local remoteUrl = (localResInfo and localResInfo.remoteUrl) or 'http://127.0.0.1:8000/resinfo.lua'
    downloadResInfo(remoteUrl)
    checkUpdateHandler = callback
end

local function compaireDiff()
    if remoteResInfo then
        if not localResInfo then
            --diffResDict = updater.clone(localResInfo.resDict)
            for id, info in pairs(remoteResInfo.resDict) do
                diffResDict[id] = info
            end
        else
            localResDict = localResInfo.resDict
            remoteResDict = remoteResInfo.resDict
            for id, info in pairs(remoteResDict) do
                localInfo = remoteResDict[id]
                if not localInfo then
                    diffResDict[id] = info
                elseif localInfo.md5 ~= info.md5 then
                    diffResDict[id] = info
                end
            end
        end
    end
end

function updater.onOneFileDownload(filename, isok)
    if curDownloadFiles ~= totalNeedDownloadFiles then
        if updateProcessHander then updateProcessHander(curDownloadFiles, totalNeedDownloadFiles) end
        return
    end
    if errorDownloadFiles > 0 then
        updater.onDownloadAllFiles(false)
    else
        updater.onDownloadAllFiles(true)
    end
end

local function copyOneFile(relativeFileName)
    -- Create nonexistent directory in update res.
    local i,j = 1,1
    while true do
        j = string.find(relativeFileName, "/", i)
        if j == nil then break end
        local dir = string.sub(relativeFileName, 1,j)
        -- Save created directory flag to a table because
        -- the io operation is too slow.
        if not updater._dirList[dir] then
            updater._dirList[dir] = true
            local fullUDir = writablePath .. dir
            updater.mkdir(fullUDir)
        end
        i = j + 1
    end
    local fullFileInURes = writablePath .. relativeFileName
    local fullFileInUTmp = tmpdir .. relativeFileName
    print(string.format('copy %s to %s', fullFileInUTmp, fullFileInURes))
    local zipFileContent = updater.readFile(fullFileInUTmp)
    if zipFileContent then
        updater.writeFile(fullFileInURes, zipFileContent)
        return fullFileInURes
    end
    return nil
end

function updater.onDownloadAllFiles(isok)
    if isok then --copy files to real dir
        for id, info in pairs(diffResDict) do
            copyOneFile(id)
        end
        copyOneFile(resInfoRelativePath)
        updater.rmdir(tmpdir)
    end
    if updateCompleteHander then updateCompleteHander(isok) end
end

function updater.startUpdate(onProcessCallback, onCompleteCallback)
    compaireDiff()
    for id, info in pairs(diffResDict) do
        downloadRes(remoteResInfo.resUrl, id)
        totalNeedDownloadFiles = totalNeedDownloadFiles + 1
    end
    curDownloadFiles = 0
    errorDownloadFiles = 0

    updateCompleteHander = onprocessCallback
    updateProcessHander = onCompleteCallback
end

--local localpath = cc.FileUtils:getInstance():getWritablePath() .. 'tmp/'
--updater.rmdir(localpath)
return updater
