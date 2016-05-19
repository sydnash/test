
#include "cocos2dx_manual.h"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#if defined(_MSC_VER) || defined(__MINGW32__)
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#endif

//self headers
#include "lua_extensions.h"
#include "updater/lua_UpdaterHelper_auto.hpp"
#include "proto/lua_BinaryStream_manual.hpp"
#include "custom_lua_listener/lua_LuaEventListener_manual.hpp"
#include "luaext/int64/lint64.h"
#include "luaext/int64/ulint64.h"

using namespace cocos2d;

int register_all_extend_module(lua_State* L)
{
	luaopen_int64(L);
	luaopen_uint64(L);
	return 0;
}
