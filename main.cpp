#include <iostream>
#include <stdio.h>
#include <list>
#include <map>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

int _TestFunc(lua_State* L)
{
	std::string val = lua_tostring(L, -1 );
	std::cout << "_TestFunc: " << val.c_str() << std::endl;

	return 1;
}

clock_t ssclock;

int _StartClock(lua_State*L)
{
	ssclock = clock();
	return 0;
}

int _EndClock(lua_State*L)
{
	auto rr = clock() - ssclock;
	std::cout << "total time: " << rr << "ms" << std::endl;
	return 0;
}

int main(void)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);   /* opens the standard libraries */

	std::map<int, std::string> mapTest;
	mapTest.insert(std::make_pair(3, "ABC"));
	mapTest.insert(std::make_pair(4, "aaa"));
	mapTest.insert(std::make_pair(2, "bbb"));
	mapTest.insert(std::make_pair(8, "ddd"));


	auto dummyNumber = [](lua_State*L) -> int{
		lua_pushinteger(L, 2);
		lua_pushinteger(L, 5);
		return 2;
	};

	auto dummyData = [](lua_State*L) -> int{
		lua_newtable(L);

		int top = lua_gettop(L);

		lua_pushinteger(L, 33);
		lua_setfield(L, -2, "dummy1");

		lua_pushstring(L, "EEE");
		lua_setfield(L, -2, "dummy2");

		lua_settop(L, top);

		return 1;
	};

	auto dummyList = [](lua_State*L) -> int{;
		lua_newtable(L);
		/* lua_createtable(L, 10, 0); */
		int top = lua_gettop(L);

		for(int i = 0 ; i < 10 ; ++i)
		{
			/* printf("i: %d\n", i); */
			lua_pushnumber(L, i+100);
			lua_rawseti(L, top, i+1); // lua_rawseti can't begin start at 0
		}

		return 1;
	};


	auto dummyMap = [](lua_State*L) -> int{;
		lua_newtable(L);
		/* lua_createtable(L, 10, 0); */
		int top = lua_gettop(L);

		for(int i = 0 ; i < 10 ; ++i)
		{
			std::string s = std::to_string(i);
			lua_pushlstring(L, s.c_str(), s.length());
			/* lua_pushlstring(L, s.c_str(), s.length()); */
			lua_pushnumber(L, i);
			lua_settable(L, top);
		}

		return 1;
	};



	auto dummyListMap = [](lua_State*L) -> int{;
		lua_newtable(L);
		int list = lua_gettop(L);

		for(int i = 0 ; i < 10 ; ++i)
		{
			lua_newtable(L);
			int map = lua_gettop(L);

			for(int n = 0 ; n < 2 ; ++n)
			{
				std::string s = std::to_string(n);
				lua_pushlstring(L, s.c_str(), s.length());
				lua_pushnumber(L, n + 100 * i);
				lua_settable(L, map);
			}

			/* lua_pushvalue(L, -1); */
			lua_rawseti(L, list, i + 1); // lua_rawseti can't begin start at 0
		}

		return 1;
	};



	lua_register(L, "dummyNumber", dummyNumber);
	lua_register(L, "dummyData", dummyData);
	lua_register(L, "dummyList", dummyList);
	lua_register(L, "dummyMap", dummyMap);
	lua_register(L, "dummyListMap", dummyListMap);
	lua_register(L, "TestFunc", _TestFunc);
	lua_register(L, "startClock", _StartClock);
	lua_register(L, "endClock", _EndClock);


	/* luaL_dostring(L, "print 'HI!'"); */
	auto err = luaL_dofile(L, "test.lua");
	if (err == 0)
	{
		lua_getglobal(L, "main");
		if( lua_isfunction(L, -1) )
		{
			if ( lua_pcall(L, 0, 0, 0) != 0 )
			{
				std::cout << "error to call function" << std::endl;
			}
		}
		else
		{
			std::cout << "not found function" << std::endl;
		}
	}

	lua_close(L);

	std::cout << "c++" << std::endl;

	_StartClock(NULL);

	double ee = 111;
	for( int i = 1 ; i < 100000 ; ++i )
	{
		ee *= i;
	}

	_EndClock(NULL);

	return 0;
}

