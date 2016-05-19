#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"
#include "proto/lua_BinaryStream_manual.hpp"
#include "custom_lua_listener/lua_custom_listener.h"
#include "custom_lua_listener/lua_LuaEventListener_manual.hpp"
#include "proto/binary_stream_proto.h"
#include "updater/lua_UpdaterHelper_auto.hpp"
#include "luaext/lua_extensions.h"
#include "luaext/cocos2dx_manual.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX)
#include "ide-support/CodeIDESupport.h"
#endif

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
#include "runtime/Runtime.h"
#include "ide-support/RuntimeLuaImpl.h"
#endif
#include "ide-support/lua_debugger.h"
using namespace CocosDenshion;

int luaopen_pb(lua_State* L);

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    RuntimeEngine::getInstance()->end();
#endif

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // set default FPS
    Director::getInstance()->setAnimationInterval(1.0 / 60.0f);

    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);
	registTestFunc(L);
	luaopen_lua_extensions_user(L);
	register_all_extend_module(L);
	register_all_binarystream_manual(L);
	register_all_luaeventlistener_manual(L);
	register_all_UpdaterHelper(L);
	luaopen_pb(L);
	//luaopen_lfs(L);
    register_all_packages();

    LuaStack* stack = engine->getLuaStack();
	auto key = "test";
	auto sign = "test";
	stack->setXXTEAKeyAndSign(key, strlen(key), sign, strlen(sign));

    //register custom function
    //LuaStack* stack = engine->getLuaStack();
    //register_custom_function(stack->getLuaState());

	auto schedule = Director::getInstance()->getScheduler();
	auto luaCustomManager = cocoslua_ext::LuaCustomEventManager::getInstance();
	schedule->schedule([luaCustomManager](float dt) {
		//unsigned char buff[20];
		//memset(buff, 0, 20);
		//memset(buff, 'a', 10);
		auto stream = cocoslua_ext::BinaryStream::create(100);
		stream->writeInt(100);
		stream->writeInt(101);
		int len = 0;
		auto buff = stream->getTotalBuff(&len);
		luaCustomManager->dispatchEvent((unsigned char*)buff, len);
	}, luaCustomManager, 2, false, "luacustommanager");
	//auto lister = cocoslua_ext::LuaCustomEventListener::create(luaCustomManager, nullptr);
	//auto dispatcher = Director::getInstance()->getEventDispatcher();
	//dispatcher->addEventListenerWithFixedPriority(lister, 1);

	int a = 0X74757678;
	char b = *(char*)&a;
#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    auto runtimeEngine = RuntimeEngine::getInstance();
    runtimeEngine->addRuntime(RuntimeLuaImpl::create(), kRuntimeEngineLua);
    runtimeEngine->start();
#else
	std::string filename = "src/main.lua";
	auto writeablepath = FileUtils::getInstance()->getWritablePath();
	auto path = writeablepath + filename;
	if (FileUtils::getInstance()->isFileExist(path)) {
		filename = path;
	}
    if (engine->executeScriptFile(filename.c_str()))
    {
        return false;
    }
#endif

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
