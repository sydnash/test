#include "lua_BinaryStream_auto.hpp"
#include "binary_stream_proto.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_binarystream_BinaryStream_reset(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::BinaryStream* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccluaext.BinaryStream",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocoslua_ext::BinaryStream*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_binarystream_BinaryStream_reset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_binarystream_BinaryStream_reset'", nullptr);
            return 0;
        }
        cobj->reset();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.BinaryStream:reset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_binarystream_BinaryStream_reset'.",&tolua_err);
#endif

    return 0;
}
int lua_binarystream_BinaryStream_readInt(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::BinaryStream* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccluaext.BinaryStream",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocoslua_ext::BinaryStream*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_binarystream_BinaryStream_readInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_binarystream_BinaryStream_readInt'", nullptr);
            return 0;
        }
        int ret = cobj->readInt();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.BinaryStream:readInt",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_binarystream_BinaryStream_readInt'.",&tolua_err);
#endif

    return 0;
}
int lua_binarystream_BinaryStream_writeInt(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::BinaryStream* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccluaext.BinaryStream",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocoslua_ext::BinaryStream*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_binarystream_BinaryStream_writeInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccluaext.BinaryStream:writeInt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_binarystream_BinaryStream_writeInt'", nullptr);
            return 0;
        }
        cobj->writeInt(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.BinaryStream:writeInt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_binarystream_BinaryStream_writeInt'.",&tolua_err);
#endif

    return 0;
}
int lua_binarystream_BinaryStream_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccluaext.BinaryStream",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccluaext.BinaryStream:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_binarystream_BinaryStream_create'", nullptr);
            return 0;
        }
        cocoslua_ext::BinaryStream* ret = cocoslua_ext::BinaryStream::create(arg0);
        object_to_luaval<cocoslua_ext::BinaryStream>(tolua_S, "ccluaext.BinaryStream",(cocoslua_ext::BinaryStream*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccluaext.BinaryStream:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_binarystream_BinaryStream_create'.",&tolua_err);
#endif
    return 0;
}
int lua_binarystream_BinaryStream_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocoslua_ext::BinaryStream* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_binarystream_BinaryStream_constructor'", nullptr);
            return 0;
        }
        cobj = new cocoslua_ext::BinaryStream();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccluaext.BinaryStream");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.BinaryStream:BinaryStream",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_binarystream_BinaryStream_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_binarystream_BinaryStream_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BinaryStream)");
    return 0;
}

int lua_register_binarystream_BinaryStream(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccluaext.BinaryStream");
    tolua_cclass(tolua_S,"BinaryStream","ccluaext.BinaryStream","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"BinaryStream");
        tolua_function(tolua_S,"new",lua_binarystream_BinaryStream_constructor);
        tolua_function(tolua_S,"reset",lua_binarystream_BinaryStream_reset);
        tolua_function(tolua_S,"readInt",lua_binarystream_BinaryStream_readInt);
        tolua_function(tolua_S,"writeInt",lua_binarystream_BinaryStream_writeInt);
        tolua_function(tolua_S,"create", lua_binarystream_BinaryStream_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocoslua_ext::BinaryStream).name();
    g_luaType[typeName] = "ccluaext.BinaryStream";
    g_typeCast["BinaryStream"] = "ccluaext.BinaryStream";
    return 1;
}
TOLUA_API int register_all_binarystream(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccluaext",0);
	tolua_beginmodule(tolua_S,"ccluaext");

	lua_register_binarystream_BinaryStream(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

