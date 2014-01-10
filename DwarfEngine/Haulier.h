#pragma once
#include <vector>
#include <queue>
#include "Dwarf.h"
#include "Modifier.h"
#include "Ease.h"


struct HaulierRoute {
	int fromX;
	int fromY;
	int dX;
	int dY;
	int duration;
	EaseType easeType;
};

class Haulier : public Modifier
{
public:
	Haulier(void);
	
	~Haulier(void);

	virtual void onRender(Uint32 deltaTime);
	virtual void onHalt(void);
	//fromX,fromY koordinatlarindan baslayarak gider
	void addRoute(int fromX, int fromY, int toX, int toY, int duration, EaseType easeType);
	//Nerdeyse ordan baslar gider
	void addRoute(int toX, int toY, int duration, EaseType easeType);


private:
	//execute all routes
	void move(Uint32 deltaTime);

	std::queue<HaulierRoute*> routes;
	HaulierRoute* currentRoute;
	SDL_Point curPos;
	void clearRoutes(void);

};

