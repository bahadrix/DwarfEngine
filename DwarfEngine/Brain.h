#pragma once
#include "modifier.h"
#include "Script.h"
#include <iostream>

class Brain :
	public Modifier
{
public:
	Brain(void);
	~Brain(void);
	void startThinking(const char* neuronFile);
	void onNeuronLoaded(void);
	virtual void onRender(Uint32 deltaTime);
	virtual void onHalt(void);
	virtual void onStop(void);
	virtual void onAttached(void);


private:
	/* the Lua interpreter */
	lua_State* L;
};

static int brain_message( lua_State *lua ) {
	std::cout << "Brain message" << std::endl;
	return 0;
}

