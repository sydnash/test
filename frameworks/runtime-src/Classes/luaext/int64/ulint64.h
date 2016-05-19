#ifndef __LUA_UINT64_H__
#define __LUA_UINT64_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

unsigned long long getUint64(lua_State* L, int index);
void pushUint64(lua_State* L, unsigned long long value);
int luaopen_uint64(lua_State *L);

#endif/*__LUA_UINT64_H__*/