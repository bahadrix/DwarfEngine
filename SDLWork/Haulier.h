#pragma once
#include <vector>
#include <queue>
#include "Dwarf.h"
#include "Modifier.h"

enum class HaulierEaseType {CUBIC_IN, CUBIC_OUT, CUBIC_INOUT};

struct HaulierRoute {
	int fromX;
	int fromY;
	int dX;
	int dY;
	int duration;
	HaulierEaseType easeType;
};

class Haulier : public Modifier
{
public:
	Haulier(void);
	~Haulier(void);

	virtual void preRender(void);
	//fromX,fromY koordinatlarindan baslayarak gider
	void addRoute(int fromX, int fromY, int toX, int toY, int duration, HaulierEaseType easeType);
	//Nerdeyse ordan baslar gider
	void addRoute(int toX, int toY, int duration, HaulierEaseType easeType);
	void start(void);
	void stop(void);


	static float ease(HaulierEaseType easeType, float t,float b , float c, float d);

private:
	//execute all routes
	void move(Uint32 deltaTime);
	void resetTimer(void);
	//in miliseconds
	Uint32 startTime; 
	std::queue<HaulierRoute*> routes;
	HaulierRoute* currentRoute;
	SDL_Point curPos;

};

