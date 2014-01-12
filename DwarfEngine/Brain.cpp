#include "stdafx.h"
#include "Brain.h"
#include <iostream>

using namespace std;

Brain::Brain(void)
{
}


Brain::~Brain(void) {
}

void Brain::startThinking( const char* neuronFile ) {
	L = lua_open();
	luaL_openlibs(L);
	if(luaL_loadfile(L, neuronFile)) {
		cerr << "Lua neuran file error " << neuronFile << endl;
	}

	lua_pushcclosure(L, brain_message, 0);
	lua_setglobal(L, "sendMessage");
	if (lua_pcall (L, 0, LUA_MULTRET, 0) == 0)
	{ 
		// Push the function name onto the stack
		lua_pushstring (L, "init");
		// Function is located in the Global Table
		lua_gettable (L, LUA_GLOBALSINDEX);  
		lua_pcall (L, 0, 0, 0);
	}

}

void Brain::onRender( Uint32 deltaTime ){}

void Brain::onHalt( void ){}


void Brain::onStop( void ){}

void Brain::onAttached( void ){
	
}


