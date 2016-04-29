/*
** LuaFileSystem
** Copyright Kepler Project 2003 (http://www.keplerproject.org/luafilesystem)
**
** $Id: lfs.h,v 1.5 2008/02/19 20:08:23 mascarenhas Exp $
*/

#if __cplusplus
extern "C" {
#endif

#ifndef __LUA_LFS_H_
#define __LUA_LFS_H_

/* Define 'chdir' for systems that do not implement it */
#ifdef NO_CHDIR
#define chdir(p)	(-1)
#define chdir_error	"Function 'chdir' not provided by system"
#else
#define chdir_error	strerror(errno)
#endif


int luaopen_lfs (lua_State *L);

#if __cplusplus
}
#endif

#endif
