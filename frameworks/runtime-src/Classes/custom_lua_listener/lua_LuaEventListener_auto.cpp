#include "lua_LuaEventListener_auto.hpp"
#include "lua_custom_listener.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_luaeventlistener_LuaCustomEventManager_getEventName(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::LuaCustomEventManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccluaext.LuaCustomEventManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocoslua_ext::LuaCustomEventManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_luaeventlistener_LuaCustomEventManager_getEventName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_luaeventlistener_LuaCustomEventManager_getEventName'", nullptr);
            return 0;
        }
        const std::string ret = cobj->getEventName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.LuaCustomEventManager:getEventName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_luaeventlistener_LuaCustomEventManager_getEventName'.",&tolua_err);
#endif

    return 0;
}
int lua_luaeventlistener_LuaCustomEventManager_dispatchEvent(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::LuaCustomEventManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccluaext.LuaCustomEventManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocoslua_ext::LuaCustomEventManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_luaeventlistener_LuaCustomEventManager_dispatchEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned char* arg0;
        int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccluaext.LuaCustomEventManager:dispatchEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_luaeventlistener_LuaCustomEventManager_dispatchEvent'", nullptr);
            return 0;
        }
        cobj->dispatchEvent(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.LuaCustomEventManager:dispatchEvent",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_luaeventlistener_LuaCustomEventManager_dispatchEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_luaeventlistener_LuaCustomEventManager_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccluaext.LuaCustomEventManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_luaeventlistener_LuaCustomEventManager_getInstance'", nullptr);
            return 0;
        }
        cocoslua_ext::LuaCustomEventManager* ret = cocoslua_ext::LuaCustomEventManager::getInstance();
        object_to_luaval<cocoslua_ext::LuaCustomEventManager>(tolua_S, "ccluaext.LuaCustomEventManager",(cocoslua_ext::LuaCustomEventManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccluaext.LuaCustomEventManager:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_luaeventlistener_LuaCustomEventManager_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_luaeventlistener_LuaCustomEventManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LuaCustomEventManager)");
    return 0;
}

int lua_register_luaeventlistener_LuaCustomEventManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccluaext.LuaCustomEventManager");
    tolua_cclass(tolua_S,"LuaCustomEventManager","ccluaext.LuaCustomEventManager","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"LuaCustomEventManager");
        tolua_function(tolua_S,"getEventName",lua_luaeventlistener_LuaCustomEventManager_getEventName);
        tolua_function(tolua_S,"dispatchEvent",lua_luaeventlistener_LuaCustomEventManager_dispatchEvent);
        tolua_function(tolua_S,"getInstance", lua_luaeventlistener_LuaCustomEventManager_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocoslua_ext::LuaCustomEventManager).name();
    g_luaType[typeName] = "ccluaext.LuaCustomEventManager";
    g_typeCast["LuaCustomEventManager"] = "ccluaext.LuaCustomEventManager";
    return 1;
}

int lua_luaeventlistener_LuaCustomEventListener_init(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::LuaCustomEventListener* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccluaext.LuaCustomEventListener",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocoslua_ext::LuaCustomEventListener*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_luaeventlistener_LuaCustomEventListener_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocoslua_ext::LuaCustomEventManager* arg0;
        std::function<void (cocoslua_ext::LuaCustomEvent *)> arg1;

        ok &= luaval_to_object<cocoslua_ext::LuaCustomEventManager>(tolua_S, 2, "ccluaext.LuaCustomEventManager",&arg0, "ccluaext.LuaCustomEventListener:init");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_luaeventlistener_LuaCustomEventListener_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.LuaCustomEventListener:init",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_luaeventlistener_LuaCustomEventListener_init'.",&tolua_err);
#endif

    return 0;
}
int lua_luaeventlistener_LuaCustomEventListener_clone(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::LuaCustomEventListener* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccluaext.LuaCustomEventListener",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocoslua_ext::LuaCustomEventListener*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_luaeventlistener_LuaCustomEventListener_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_luaeventlistener_LuaCustomEventListener_clone'", nullptr);
            return 0;
        }
        cocoslua_ext::LuaCustomEventListener* ret = cobj->clone();
        object_to_luaval<cocoslua_ext::LuaCustomEventListener>(tolua_S, "ccluaext.LuaCustomEventListener",(cocoslua_ext::LuaCustomEventListener*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.LuaCustomEventListener:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_luaeventlistener_LuaCustomEventListener_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_luaeventlistener_LuaCustomEventListener_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::LuaCustomEventListener* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_luaeventlistener_LuaCustomEventListener_constructor'", nullptr);
            return 0;
        }
        cobj = new cocoslua_ext::LuaCustomEventListener();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccluaext.LuaCustomEventListener");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.LuaCustomEventListener:LuaCustomEventListener",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_luaeventlistener_LuaCustomEventListener_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_luaeventlistener_LuaCustomEventListener_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LuaCustomEventListener)");
    return 0;
}

int lua_register_luaeventlistener_LuaCustomEventListener(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccluaext.LuaCustomEventListener");
    tolua_cclass(tolua_S,"LuaCustomEventListener","ccluaext.LuaCustomEventListener","cc.EventListenerCustom",nullptr);

    tolua_beginmodule(tolua_S,"LuaCustomEventListener");
        tolua_function(tolua_S,"new",lua_luaeventlistener_LuaCustomEventListener_constructor);
        tolua_function(tolua_S,"init",lua_luaeventlistener_LuaCustomEventListener_init);
        tolua_function(tolua_S,"clone",lua_luaeventlistener_LuaCustomEventListener_clone);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocoslua_ext::LuaCustomEventListener).name();
    g_luaType[typeName] = "ccluaext.LuaCustomEventListener";
    g_typeCast["LuaCustomEventListener"] = "ccluaext.LuaCustomEventListener";
    return 1;
}
TOLUA_API int register_all_luaeventlistener(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccluaext",0);
	tolua_beginmodule(tolua_S,"ccluaext");

	lua_register_luaeventlistener_LuaCustomEventListener(tolua_S);
	lua_register_luaeventlistener_LuaCustomEventManager(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

