#pragma once
#include <SDL.h>
#include <vector>

class Dwarf;
class Modifier {
public:
	static enum class StopState {NATURAL, MANUAL, HALT};
	Modifier(void);
	Modifier(char* name);
	~Modifier(void);
	void preRender(void);
	virtual void onRender(Uint32 deltaTime);
	virtual void onHalt(void);
	virtual void onStop(void);
	virtual void onAttached(void);
	void start(void);
	void stop(void);
	void halt(void);
	bool isRunning();
	void setName(char* name);
	std::vector<Modifier*> impersonators;
	std::vector<Modifier*> followers;
	char* name;	
protected:
	void stop(StopState state);
	void resetTimer(void);
	//in milliseconds
	Uint32 startTime; 
	Dwarf *target;
	
	friend class Dwarf;
};

