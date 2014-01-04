#include "stdafx.h"
#include "Modifier.h"


Modifier::Modifier(void) {

}


Modifier::~Modifier(void)
{
}

void Modifier::preRender(void) {};

void Modifier::start( void ) {
	if(startTime == NULL) {
		resetTimer();
	}
}

void Modifier::stop( void ){
	startTime = NULL;
}



void Modifier::resetTimer( void ) {
	startTime = SDL_GetTicks();
}
void Modifier::halt( void )
{
	stop();
	onHalt();

}

void Modifier::onHalt( void ) {}
