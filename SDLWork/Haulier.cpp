#include "stdafx.h"
#include "Haulier.h"
#include <iostream>
#include "Ease.h"


Haulier::Haulier(void) {
	startTime = NULL;
}


Haulier::~Haulier(void) {
}



void Haulier::addRoute( int fromX, int fromY, int toX, int toY, int duration, EaseType easeType )
{

	//HaulierRoute route = {fromX, fromY, toX - fromX, toY - fromY, duration, easeType};
	HaulierRoute *route = new HaulierRoute; //dinamik olara atamazsan sonra sapitiyo pzvnk
	route->duration = duration;
	route->dX = toX - fromX;
	route->dY = toY - fromY;
	route->fromX = fromX;
	route->fromY = fromY;
	route->easeType = easeType;
	routes.push(route);
	
	
	//printf("\nRoute added: from(%d, %d) delta(%d, %d)",routes.front()->fromX, routes.front()->fromY, routes.front()->dX, routes.front()->dY);


}

void Haulier::addRoute( int toX, int toY, int duration, EaseType easeType ) {
	HaulierRoute *route = new HaulierRoute; //dinamik olara atamazsan sonra sapitiyo pzvnk
	route->duration = duration;
	route->dX = toX;
	route->dY = toY;
	route->fromX = NULL;
	route->fromY = NULL;
	route->easeType = easeType;
	routes.push(route);
}


void Haulier::move( Uint32 deltaTime ) {
	
	if(routes.empty()) {
		stop();
		return;
	}
	target->getPosition(&curPos);

	if(currentRoute == NULL) {
		currentRoute = routes.front();
		if(currentRoute->fromX == NULL) {
			currentRoute->fromX = curPos.x;
			currentRoute->dX = currentRoute->dX - currentRoute->fromX;
		}
		if(currentRoute->fromY == NULL) {
			currentRoute->fromY = curPos.y;
			currentRoute->dY = currentRoute->dY - currentRoute->fromY;
		}
	}
	

	if(deltaTime > currentRoute->duration)
		deltaTime = currentRoute->duration;


	

	curPos.x = ceil(Ease::get(currentRoute->easeType, deltaTime, currentRoute->fromX, currentRoute->dX, currentRoute->duration));
	curPos.y = ceil(Ease::get(currentRoute->easeType, deltaTime, currentRoute->fromY, currentRoute->dY, currentRoute->duration));
	//printf("Time: %d/%u Current Pos:(%d, %d) Delta:(%d, %d)\n", deltaTime, currentRoute->duration, curPos.x, curPos.y, currentRoute->dX, currentRoute->dY);
	
	target->translate(&curPos);

	if (deltaTime == currentRoute->duration) {
		routes.pop();
		currentRoute = NULL;
		resetTimer(); // reset timer
	}
		
}



void Haulier::preRender( void ) {

	if(startTime != NULL) { // set this NULL to stop/bypass
		move(SDL_GetTicks() - startTime);
	}
}

void Haulier::start( void ) {
	if(startTime == NULL) {
		resetTimer();
	}
}

void Haulier::stop( void ){
	startTime = NULL;
}



void Haulier::resetTimer( void ) {
	startTime = SDL_GetTicks();
}

void Haulier::clearRoutes( void )
{
	if(!routes.empty())
		std::queue<HaulierRoute*>().swap(routes);
}

void Haulier::halt( void )
{
	stop();
	currentRoute = NULL;
	clearRoutes();

}


