/*
* lint64.c
* int64 nummbers for Lua
* Luiz Henrique de Figueiredo <lhf@tecgraf.puc-rio.br>
* 05 Aug 2013 21:04:25
* This code is hereby placed in the public domain.
*/
#include <assert.h>

extern "C" {
#include "lualib.h"
#include "lauxlib.h"
}

#include <stdlib.h>
#include <errno.h>

static unsigned long long  
	atoull (const char *p)  
{  
	//int minus = 0;  
	unsigned long long value = 0;  
	if (*p == '-')  
	{  
		//minus ++;  
		//p ++;  
		assert(false);
	}  
	while (*p >= '0' && *p <= '9')  
	{  
		value *= 10;  
		value += *p - '0';  
		p ++;  
	}  
	return value;/*minus ? 0 - value : value;  */
}  

#define Int		unsigned long long
#define FMT		"%llu"
#define atoI		atoull

#include "lua.h"
#include "lauxlib.h"

#define MYNAME		"uint64"
#define MYTYPE		MYNAME
#define MYVERSION	MYTYPE " library for " LUA_VERSION " / Aug 2013"

#define Z(i)		Pget(L,i)
#define	I(x)		((Int)x)

static Int Pget(lua_State *L, int i)
{
	switch (lua_type(L,i))
	{
	case LUA_TNUMBER:
		return luaL_checknumber(L,i);
	case LUA_TSTRING:
		return atoI(luaL_checkstring(L,i));
	default:
		return *((Int*)luaL_checkudata(L,i,MYTYPE));
	}
}

unsigned long long getUint64(lua_State* L, int index)
{
	return Z(index);
}

static int pushInt(lua_State *L, Int z)
{
	Int *p=(Int *)lua_newuserdata(L,sizeof(Int));
	*p=z;
	luaL_getmetatable(L,MYTYPE);
	lua_setmetatable(L,-2);
	return 1;
}

void pushUint64(lua_State* L, unsigned long long value)
{
	pushInt(L, value);
}

static int Lpow(lua_State *L)			/** __pow(z,n) */
{
	Int z=Z(1);
	Int n=Z(2);
	Int r;
	if (z==I(2))
		r= (n>=8*sizeof(Int)) ? 0 : (I(1)<<n);
	else
	{
		for (r=1; n>0; n>>=1)
		{
			if (n&1) r*=z;
			z*=z;
		}
	}
	return pushInt(L,r);
}

static int Ltostring(lua_State *L)		/** __tostring(z) */
{
	char b[64];
	sprintf(b,FMT,Z(1));
	lua_pushstring(L,b);
	return 1;
}

static int Ltonumber(lua_State *L)		/** tonumber(z) */
{
	lua_pushnumber(L,(lua_Number)Z(1));
	return 1;
}

#define add(z,w)	((z)+(w))
#define sub(z,w)	((z)-(w))
#define mod(z,w)	((z)%(w))
#define mul(z,w)	((z)*(w))
#define div(z,w)	((z)/(w))
#define neg(z)		(-(z))
#define new(z)		(z)
#define eq(z,w)		((z)==(w))
#define le(z,w)		((z)<=(w))
#define lt(z,w)		((z)<(w))

#define A(f,e)	static int L##f(lua_State *L) { return pushInt(L,e); }
#define B(f)	A(f,f(Z(1),Z(2)))
#define F(f)	A(f,f(Z(1)))
#define T(f)	C(f,f(Z(1),Z(2)))
#define C(f,e)	static int L##f(lua_State *L) { lua_pushboolean(L,e); return 1; }

B(add)			/** __add(z,w) */
	B(div)			/** __div(z,w) */
	B(mod)			/** __mod(z,w) */
	B(mul)			/** __mul(z,w) */
	B(sub)			/** __sub(z,w) */
	//F(neg)			/** __unm(z) */
	F(new)			/** new(z) */
	T(eq)			/** __eq(z,w) */
	T(le)			/** __le(z,w) */
	T(lt)			/** __lt(z,w) */

	static const luaL_Reg R[] =
{
	{ "__add",	Ladd	},
	{ "__div",	Ldiv	},
	{ "__eq",	Leq	},
	{ "__le",	Lle	},
	{ "__lt",	Llt	},
	{ "__mod",	Lmod	},
	{ "__mul",	Lmul	},
	{ "__pow",	Lpow	},
	{ "__sub",	Lsub	},
	//{ "__unm",	Lneg	},
	{ "__tostring",	Ltostring},
	{ "new",	Lnew	},
	{ "tonumber",	Ltonumber},
	{ NULL,		NULL	}
};

int luaopen_uint64(lua_State *L)
{
	if (sizeof(Int)<8) luaL_error(L,"int64 cannot work with %d-byte values",sizeof(Int));
	luaL_newmetatable(L, MYTYPE); /*stack: mt*/
	lua_setglobal(L, MYNAME); /*_G[MYNAME] = mt stack: */
	luaL_register(L, MYNAME, R); /*_G[MYNAME].__add = ..., _G[MYNAME].__div = ldiv.. stack: mt*/
	lua_pushliteral(L,"version");			/** version */
	lua_pushliteral(L, MYVERSION); 
	lua_settable(L,-3);  /*mt[version] = MYVERSION, stack:mt*/
	pushInt(L,0);
	lua_setfield(L,-2,"min");			/** min */
	pushInt(L,ULLONG_MAX);
	lua_setfield(L,-2,"max");			/** max */

	lua_pop(L, 1);
	return 0;
}
