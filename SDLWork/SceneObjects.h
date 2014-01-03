#pragma once
#include <SDL.h>
#include "dwarf.h"
#include "Haulier.h"

class SignalButton : public Dwarf
{
public:
	virtual void onMouseEvent(SDL_Event *event);
	SignalButton(void);
	~SignalButton(void);
private:
	Haulier *haulier;
};

