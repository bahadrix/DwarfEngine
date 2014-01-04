#pragma once
#include <SDL.h>

class Dwarf;
class Modifier {
public:
	Modifier(void);
	~Modifier(void);
	virtual void preRender(void);
	virtual void onHalt(void);
	void start(void);
	void stop(void);
	void halt(void);

protected:
	void resetTimer(void);
	//in milliseconds
	Uint32 startTime; 
	Dwarf *target;

	friend class Dwarf;
};

