#include "lua_UpdaterHelper_auto.hpp"
#include "updater_helper.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_UpdaterHelper_UpdaterHelper_clear(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::UpdaterHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccluaext.UpdaterHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocoslua_ext::UpdaterHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_UpdaterHelper_UpdaterHelper_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_UpdaterHelper_UpdaterHelper_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.UpdaterHelper:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_UpdaterHelper_UpdaterHelper_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_UpdaterHelper_UpdaterHelper_downloadFile(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::UpdaterHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccluaext.UpdaterHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocoslua_ext::UpdaterHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_UpdaterHelper_UpdaterHelper_downloadFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccluaext.UpdaterHelper:downloadFile");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccluaext.UpdaterHelper:downloadFile");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccluaext.UpdaterHelper:downloadFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_UpdaterHelper_UpdaterHelper_downloadFile'", nullptr);
            return 0;
        }
        cobj->downloadFile(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.UpdaterHelper:downloadFile",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_UpdaterHelper_UpdaterHelper_downloadFile'.",&tolua_err);
#endif

    return 0;
}
int lua_UpdaterHelper_UpdaterHelper_destroy(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccluaext.UpdaterHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_UpdaterHelper_UpdaterHelper_destroy'", nullptr);
            return 0;
        }
        cocoslua_ext::UpdaterHelper::destroy();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccluaext.UpdaterHelper:destroy",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_UpdaterHelper_UpdaterHelper_destroy'.",&tolua_err);
#endif
    return 0;
}
int lua_UpdaterHelper_UpdaterHelper_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccluaext.UpdaterHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        std::string arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccluaext.UpdaterHelper:getInstance");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccluaext.UpdaterHelper:getInstance");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccluaext.UpdaterHelper:getInstance");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_UpdaterHelper_UpdaterHelper_getInstance'", nullptr);
            return 0;
        }
        cocoslua_ext::UpdaterHelper* ret = cocoslua_ext::UpdaterHelper::getInstance(arg0, arg1, arg2);
        object_to_luaval<cocoslua_ext::UpdaterHelper>(tolua_S, "ccluaext.UpdaterHelper",(cocoslua_ext::UpdaterHelper*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccluaext.UpdaterHelper:getInstance",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_UpdaterHelper_UpdaterHelper_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_UpdaterHelper_UpdaterHelper_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::UpdaterHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        std::string arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccluaext.UpdaterHelper:UpdaterHelper");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccluaext.UpdaterHelper:UpdaterHelper");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccluaext.UpdaterHelper:UpdaterHelper");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_UpdaterHelper_UpdaterHelper_constructor'", nullptr);
            return 0;
        }
        cobj = new cocoslua_ext::UpdaterHelper(arg0, arg1, arg2);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccluaext.UpdaterHelper");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.UpdaterHelper:UpdaterHelper",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_UpdaterHelper_UpdaterHelper_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_UpdaterHelper_UpdaterHelper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (UpdaterHelper)");
    return 0;
}

int lua_register_UpdaterHelper_UpdaterHelper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccluaext.UpdaterHelper");
    tolua_cclass(tolua_S,"UpdaterHelper","ccluaext.UpdaterHelper","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"UpdaterHelper");
        tolua_function(tolua_S,"new",lua_UpdaterHelper_UpdaterHelper_constructor);
        tolua_function(tolua_S,"clear",lua_UpdaterHelper_UpdaterHelper_clear);
        tolua_function(tolua_S,"downloadFile",lua_UpdaterHelper_UpdaterHelper_downloadFile);
        tolua_function(tolua_S,"destroy", lua_UpdaterHelper_UpdaterHelper_destroy);
        tolua_function(tolua_S,"getInstance", lua_UpdaterHelper_UpdaterHelper_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocoslua_ext::UpdaterHelper).name();
    g_luaType[typeName] = "ccluaext.UpdaterHelper";
    g_typeCast["UpdaterHelper"] = "ccluaext.UpdaterHelper";
    return 1;
}
TOLUA_API int register_all_UpdaterHelper(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccluaext",0);
	tolua_beginmodule(tolua_S,"ccluaext");

	lua_register_UpdaterHelper_UpdaterHelper(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

