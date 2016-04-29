#include "lua_BinaryStream_auto.hpp"
#include "binary_stream_proto.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "lua_BinaryStream_auto.hpp"

int lua_binarystream_BinaryStream_getTotalBuff(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_binarystream_BinaryStream_getTotalBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        int arg0 = 0;

        const unsigned char* ret = cobj->getTotalBuff(&arg0);
		lua_pushlstring(tolua_S, (const char*)ret, arg0);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.BinaryStream:getTotalBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_binarystream_BinaryStream_getTotalBuff'.",&tolua_err);
#endif

    return 0;
}

int lua_binarystream_BinaryStream_setBuff(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_binarystream_BinaryStream_setBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
		bool ok = lua_isstring(tolua_S, 2) == 1 ? true : false;
		size_t len = 0;
		const char* arg0 = lua_tolstring(tolua_S, 2, &len);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_binarystream_BinaryStream_setBuff'", nullptr);
            return 0;
        }
		cobj->setBuff(arg0, len);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.BinaryStream:setBuff",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_binarystream_BinaryStream_setBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_binarystream_BinaryStream_writeString(lua_State* tolua_S)
{
	int argc = 0;
	cocoslua_ext::BinaryStream* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "ccluaext.BinaryStream", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (cocoslua_ext::BinaryStream*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_binarystream_BinaryStream_writeString'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)
	{
		const char* arg0;
		size_t arg1;

		bool ok = lua_isstring(tolua_S, -1) == 1 ? true : false;
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_binarystream_BinaryStream_writeString'", nullptr);
			return 0;
		}
		arg0 = lua_tolstring(tolua_S, -1, &arg1);
		cobj->writeString(arg0, arg1);
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.BinaryStream:writeString", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_binarystream_BinaryStream_writeString'.", &tolua_err);
#endif
	return 0;
}
int lua_binarystream_BinaryStream_readString(lua_State* tolua_S)
{
	int argc = 0;
	cocoslua_ext::BinaryStream* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "ccluaext.BinaryStream", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (cocoslua_ext::BinaryStream*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_binarystream_BinaryStream_readString'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		int arg0;
		unsigned char* ret = cobj->readString(&arg0);
		lua_pushlstring(tolua_S, (const char*)ret, arg0);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccluaext.BinaryStream:readString", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_binarystream_BinaryStream_readString'.", &tolua_err);
#endif

	return 0;
}
TOLUA_API int register_all_binarystream_manual(lua_State* tolua_S)
{
	register_all_binarystream(tolua_S);
	lua_pushstring(tolua_S, "ccluaext.BinaryStream");
	lua_rawget(tolua_S, LUA_REGISTRYINDEX);
	if (lua_istable(tolua_S, -1))
	{
        tolua_function(tolua_S,"setBuff",lua_binarystream_BinaryStream_setBuff);
        tolua_function(tolua_S,"getTotalBuff",lua_binarystream_BinaryStream_getTotalBuff);
		tolua_function(tolua_S, "readString", lua_binarystream_BinaryStream_readString);
		tolua_function(tolua_S, "writeString", lua_binarystream_BinaryStream_writeString);
	}
	lua_pop(tolua_S, 1);

	return 1;
}

