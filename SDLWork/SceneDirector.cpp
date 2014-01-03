#include "stdafx.h"
#include "SceneDirector.h"
#include <SDL.h>

#define MOUSE_SENSITIVITY 1

SceneDirector::SceneDirector(void)
{
}

void SceneDirector::onMouseEvent(SDL_Event *event) {
	if(event->type == SDL_MOUSEMOTION) {
		if(SDL_BUTTON(SDL_BUTTON_RIGHT) == event->motion.state) {

			translateDelta(event->motion.xrel, event->motion.yrel);

			SDL_ShowCursor (false);
		} else {
			SDL_ShowCursor (true);
		}
	}
}
SceneDirector::~SceneDirector(void)
{
}
