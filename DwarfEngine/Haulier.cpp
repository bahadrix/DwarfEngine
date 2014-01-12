#include "stdafx.h"
#include "Haulier.h"
#include <iostream>
#include "Ease.h"


Haulier::Haulier(void) {

	stop();
}


void Haulier::onAttached( void ){
	

}

Haulier::~Haulier(void) { }




void Haulier::addRoute( int fromX, int fromY, int toX, int toY, int duration, EaseType easeType ){

	HaulierRoute *route = new HaulierRoute; //dinamik olarak atamazsan sonra sapitiyo pzvnk
	route->duration = duration;
	route->dX = toX - fromX;
	route->dY = toY - fromY;
	route->fromX = fromX;
	route->fromY = fromY;
	route->easeType = easeType;
	routes.push(route);

}

void Haulier::addRoute( int toX, int toY, int duration, EaseType easeType ) {
	HaulierRoute *route = new HaulierRoute; //dinamik olarak atamazsan sonra sapitiyo pzvnk
	route->duration = duration;
	route->dX = toX;
	route->dY = toY;
	route->fromX = NULL;
	route->fromY = NULL;
	route->easeType = easeType;
	routes.push(route);
}


void Haulier::clearRoutes( void ) {
	if(!routes.empty())
		std::queue<HaulierRoute*>().swap(routes);
}

void Haulier::onHalt( void ) {
	currentRoute = NULL;
	clearRoutes();
}

void Haulier::onRender( Uint32 deltaTime )
{
	if(routes.empty()) {
		stop(Modifier::StopState::NATURAL);
		return;
	}
	target->getPositionOnScreen(&curPos);

	if(currentRoute == NULL) { // Select next route
		dist.x = 0;
		dist.y = 0;
		lastDist.x = 0;
		lastDist.y = 0;
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

	dist.x = Ease::get(currentRoute->easeType, deltaTime, 0, currentRoute->dX, currentRoute->duration);
	dist.y = Ease::get(currentRoute->easeType, deltaTime, 0, currentRoute->dY, currentRoute->duration);
	//printf("Time: %d/%u Current Pos:(%d, %d) Delta:(%d, %d)\n", deltaTime, currentRoute->duration, curPos.x, curPos.y, currentRoute->dX, currentRoute->dY);
	
	//target->translateOnScreen(&curPos);

	target->translateDelta(dist.x - lastDist.x, dist.y - lastDist.y );

	lastDist.x = dist.x;
	lastDist.y = dist.y;

	if (deltaTime == currentRoute->duration) {
		routes.pop();
		currentRoute = NULL;
		resetTimer(); // reset timer
	}
}






