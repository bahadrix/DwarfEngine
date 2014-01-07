#include "stdafx.h"
#include "Haulier.h"
#include <iostream>
#include "Ease.h"


Haulier::Haulier(void) {
	stop();
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




