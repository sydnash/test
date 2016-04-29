#include "lua_LuaEventListener_auto.hpp"
#include "lua_custom_listener.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "lua_LuaEventListener_auto.hpp"
#include "assert.h"
#include "CCLuaEngine.h"

int lua_luaeventlistener_LuaCustomEventListener_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccluaext.LuaCustomEventListener",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S, 2, "ccluaext.LuaCustomEventManager", 0, &tolua_err) ||
			!toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err))
			goto tolua_lerror;
#endif
        cocoslua_ext::LuaCustomEventManager* arg0;
        ok &= luaval_to_object<cocoslua_ext::LuaCustomEventManager>(tolua_S, 2, "ccluaext.LuaCustomEventManager",&arg0, "ccluaext.LuaCustomEventListener:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_luaeventlistener_LuaCustomEventListener_create'", nullptr);
            return 0;
        }
		LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 3, 0);
		auto arg1 = [tolua_S, handler](cocoslua_ext::LuaCustomEvent* event) {
			int len = 0;
			auto buff = event->getBuffer(&len);
			assert(buff != nullptr);
			lua_pushlstring(tolua_S, (const char*)buff, len);
			LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 1);
		};
        cocoslua_ext::LuaCustomEventListener* ret = cocoslua_ext::LuaCustomEventListener::create(arg0, arg1);
        object_to_luaval<cocoslua_ext::LuaCustomEventListener>(tolua_S, "ccluaext.LuaCustomEventListener",(cocoslua_ext::LuaCustomEventListener*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccluaext.LuaCustomEventListener:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_luaeventlistener_LuaCustomEventListener_create'.",&tolua_err);
#endif
    return 0;
}

TOLUA_API int register_all_luaeventlistener_manual(lua_State* tolua_S)
{
	register_all_luaeventlistener(tolua_S);
	lua_pushstring(tolua_S, "ccluaext.LuaCustomEventListener");
	lua_rawget(tolua_S, LUA_REGISTRYINDEX);
	if (lua_istable(tolua_S, -1))
	{
        tolua_function(tolua_S,"create", lua_luaeventlistener_LuaCustomEventListener_create);
	}
	lua_pop(tolua_S, 1);
	return 1;
}

