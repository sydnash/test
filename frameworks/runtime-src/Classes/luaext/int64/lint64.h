#ifndef __LUA_INT64_H__
#define __LUA_INT64_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

long long getInt64(lua_State* L, int index);
void pushInt64(lua_State* L, long long value);

int luaopen_int64(lua_State *L);

#endif/*__LUA_INT64_H__*/