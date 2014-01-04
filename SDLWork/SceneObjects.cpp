#include "stdafx.h"
#include "SceneObjects.h"
#include "Haulier.h"


SignalButton::SignalButton(void) {
	haulier = new Haulier();

	this->addModifier(haulier);
}


SignalButton::~SignalButton(void) {
}

void SignalButton::onMouseEvent( SDL_Event *event )
{
	if(event->type == SDL_MOUSEBUTTONDOWN) {	
		SDL_Rect rect;
		getRectangle(&rect);
		haulier->halt();
		haulier->addRoute(event->motion.x - rect.w/2, event->motion.y - rect.h/2, 720, EaseType::CIRC_INOUT);
		haulier->start();
		//printf("\nMoving to: %d, %d", event->motion.x, event->motion.y);
	}

	
	

}
