#ifndef __luaext_cocos2dx_manual_h__
#define __luaext_cocos2dx_manual_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_extend_module(lua_State* L);
#endif
