#include "stdafx.h"
#include "Modifier.h"
#include "Dwarf.h"

Modifier::Modifier(void) {
	name = "<unknown_modifier>";
}

Modifier::Modifier( char* name ){
	this->name = name;
}


Modifier::~Modifier(void)
{
}

void Modifier::preRender(void) {
	if(startTime != NULL) { // set this NULL to stop/bypass
		onRender(SDL_GetTicks() - startTime);
	}
};

void Modifier::start( void ) {
	if(startTime == NULL) {
		resetTimer();
	}
	for(int i = 0; i < impersonators.size(); i++) {
		impersonators.at(i)->start();
	}
}

void Modifier::stop( void ){
	stop(StopState::MANUAL);
}

void Modifier::stop( StopState state ) {
	startTime = NULL;
	int i;
	for(i = 0; i < impersonators.size(); i++) {
		impersonators.at(i)->stop();
	}
	for(i = 0; i < followers.size(); i++) {
		followers.at(i)->start();
	}
	if(target != nullptr)
		target->onModifierStop(name, state);
	onStop();
}



void Modifier::resetTimer( void ) {
	startTime = SDL_GetTicks();
}

// All impersonators halted and no followers started.
void Modifier::halt( void ) {
	stop(StopState::HALT);
	onHalt();
	for(int i = 0; i < impersonators.size(); i++) {
		impersonators.at(i)->halt();
	}
}

void Modifier::onHalt( void ) {}

void Modifier::onRender( Uint32 deltaTime ){}



bool Modifier::isRunning() {
	return startTime != NULL;
}

void Modifier::setName( char* name )
{
	this->name = name;
}

void Modifier::onStop( void ){}

void Modifier::onAttached( void ){}

