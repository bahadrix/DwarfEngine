#include "stdafx.h"
#include "CharacterFour.h"


CharacterFour::CharacterFour(void){
	haulier = new Haulier();
	haulier->setName(TAG_CHARACTER_HAULIER);
	this->addModifier(haulier);
	animator = new SpriteAnimator();
	this->addModifier(animator);
	haulier->impersonators.push_back(animator);
	
	this->speed = 100;
	
	
	

}


CharacterFour::~CharacterFour(void){
}

void CharacterFour::setTexture( SpriteSlice upSlice, SpriteSlice downSlice, SpriteSlice leftSlice, SpriteSlice rightSlice, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double* angle /* = nullptr */, SDL_Point* pivot /* = NULL */, SDL_RendererFlip flip /* = SDL_RendererFlip::SDL_FLIP_NONE */ ) {
	
	SpriteDwarf::setTexture(texture, srcRect, dstRect, angle, pivot, flip);

	addAnimation(&upSlice);
	addAnimation(&downSlice);
	addAnimation(&leftSlice);
	addAnimation(&rightSlice);

	this->focusPoint.x = dstRect->w/2;
	this->focusPoint.y = dstRect->h/2;
}



void CharacterFour::move( Direction direction, int delta, Uint16 duration, EaseType easeing )
{
	animator->halt();

	SDL_Point pos;
	getPosition(&pos);

	haulier->halt();
	int x,y;
	switch (direction) {
	case CharacterFour::Direction::VERTICAL: // bunlarýn end framelerini belirle, ayaa havada kalýyo. animator stop'a eklenecek buyuk ihtimal.
		animator->addAnimationItem(delta > 0 ? 1 : 0, 500, 0, 0,0, EaseType::LINEAR);
		haulier->addRoute(pos.x, pos.y + delta, duration, easeing);
		break;
	case CharacterFour::Direction::HORIZONTAL:
		animator->addAnimationItem(delta > 0 ? 3 : 2, 500, 0, 0,0, EaseType::LINEAR);
		haulier->addRoute(pos.x + delta, pos.y, duration, easeing);
		break;
	default:
		break;
	}
	
	haulier->start();

}

void CharacterFour::onMouseEvent( SDL_Event *event ) {
	if(event->type == SDL_MOUSEBUTTONDOWN) {	
		breakMove();
		SDL_Rect rect;
		getDstRect(&rect);
		HaulierRoute *x_route = new HaulierRoute;
		HaulierRoute *y_route = new HaulierRoute;
		
		
		x_route->dX = event->motion.x - rect.x - focusPoint.y;
		x_route->dY = 0;
		x_route->duration = abs((x_route->dX*1000/speed));
		x_route->easeType = EaseType::LINEAR;
		
		
		y_route->dX = 0;
		y_route->dY = event->motion.y - rect.y - focusPoint.y;
		y_route->duration = abs((y_route->dY*1000/speed));
		y_route->easeType = EaseType::LINEAR;

		addPath(x_route);
		addPath(y_route);

		followRoute();
		//move(Direction::HORIZONTAL, event->motion.x - rect.x, 5800, EaseType::LINEAR);
		//printf("\nMoving to: %d, %d", event->motion.x, event->motion.y);
	}
}

void CharacterFour::followRoute( void ){
	if(route.empty())
		return;
	
	SDL_Point pos;
	getPosition(&pos);

	HaulierRoute *path = route.front();
	printf("\nRoute: from(%d,%d) to: (%d, %d)", pos.x, pos.y, pos.x + path->dX, pos.y + path->dY);
	if (path->dX != 0) {
		move(Direction::HORIZONTAL, path->dX, path->duration, path->easeType); 
		printf(" Horizontal");
	}
	if (path->dY != 0) {
		move(Direction::VERTICAL, path->dY, path->duration, path->easeType); 
		printf(" Vertical");
	}

	route.pop();
	

}

void CharacterFour::addPath( HaulierRoute *path ) {
	route.push(path);
}

void CharacterFour::onModifierStop( char* name, Modifier::StopState state ) {
	if(name == TAG_CHARACTER_HAULIER && state == Modifier::StopState::NATURAL) {
		followRoute();
	}
} 

void CharacterFour::breakMove( void ){
	haulier->halt();
	queue<HaulierRoute*>().swap(route);
}
