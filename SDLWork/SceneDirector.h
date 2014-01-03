#pragma once
#include <SDL.h>
#include "dwarf.h"

class SceneDirector :
	public Dwarf
{
public:
	SceneDirector(void);
	// Overriding mouse event
	virtual void onMouseEvent(SDL_Event *event);
	~SceneDirector(void);
};

