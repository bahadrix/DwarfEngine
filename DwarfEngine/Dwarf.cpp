#include "stdafx.h"
#include "iostream"
#include "Dwarf.h"
#include <vector>
#include <queue>


Dwarf::Dwarf(SDL_Renderer* renderer, Dwarf *parent){	
	init(renderer, parent);
}

Dwarf::Dwarf() {
	init(NULL, NULL);	
}
void Dwarf::init( SDL_Renderer* renderer, Dwarf *parent ) {
	this->renderer = renderer;
	this->parent = parent;
	SDL_Rect initialSrcRect = {0,0,0,0};
	SDL_Rect initialDstRect = {0,0,0,0};
	this->srcRect = &initialSrcRect;
	this->dstRect = &initialDstRect;
	if(parent == NULL) {

		parentDst = new SDL_Rect;
		parentDst->w = 0;
		parentDst->h = 0;
		parentDst->x = 0;
		parentDst->y = 0;

	} else {
		parentDst = parent->dstRect;
	}
	this->name = "<noname>";
}
Dwarf* Dwarf::breed() {
	
	Dwarf* baby = new Dwarf();
	adopt(baby);
	return baby;
}
void Dwarf::adopt( Dwarf* child ) {
	child->renderer = this->renderer;
	children.push_back(child);
	child->parent = this;


	
}


void Dwarf::render(void) {
	preRender();
	if(this->texture != nullptr) {
		if(angle != nullptr) {
			//Convert pivot from relative to object's top-left corner to be relative to its center
			SDL_Point pivotc = { pivot->x + dstRect->w/2, pivot->y + dstRect->h/2 };
			//Draw the texture
			SDL_RenderCopyEx(renderer, texture, srcRect, dstRect, *angle, &pivotc, flip);
		} else {
			SDL_RenderCopy(renderer, texture, srcRect, dstRect);
		}
	}
}


/************************************************************************/
/* If it's sprite, sheet size is calculated by srcRect                  */
/************************************************************************/
void Dwarf::setTexture( SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double* angle /*= nullptr*/, SDL_Point* pivot /*= NULL*/, SDL_RendererFlip flip /*= SDL_RendererFlip::SDL_FLIP_NONE*/ )
{
	this->texture = texture;
	this->srcRect = srcRect;
	this->dstRect = dstRect;	
	this->angle = angle;
	this->pivot = pivot;
	this->flip = flip;
	onTextureSet();
}

Dwarf::~Dwarf(void){
	if(this->texture != nullptr) // Have a texture
		SDL_DestroyTexture(texture);

	//Clear by depth first
	for(int c=0; c < children.size(); c++) {
		Dwarf* child = children.back();
		children.pop_back();
		delete child;
		
	}

}

void Dwarf::translateDelta( int dx, int dy ) {
	dstRect->x += dx;
	dstRect->y += dy;

	//Depth first bound
	for(int c=0; c < children.size(); c++)
		children.at(c)->translateDelta(dx, dy);
}

//Translate to point on the parent
void Dwarf::translateOnScreen( int x, int y ) {
	//x,y: position on parent local
	//dstRect: position screen
	translateDelta(x - dstRect->x - parentDst->x, y - dstRect->y - parentDst->y);
}

void Dwarf::translateOnScreen( SDL_Point *destination ) {
	translateOnScreen(destination->x, destination->y);
}

void Dwarf::onMouseEvent( SDL_Event *event ) {

}

bool Dwarf::isInRect( int x, int y ) {
	if(
		x > dstRect->x && x < dstRect->x + dstRect->w &&
		y > dstRect->y && y < dstRect->y + dstRect->h) {
		return 1;
	} else {
		return 0;
	}
}


void Dwarf::preRender( void ) {
	
	for(std::vector<Modifier*>::iterator modifierIterator = modifiers.begin(); modifierIterator != modifiers.end(); ++modifierIterator) {
		(*modifierIterator)->preRender(); 
	}
	
}

void Dwarf::addModifier( Modifier* modifier ) {
	modifier->target = this;
	modifiers.push_back(modifier);
	modifier->onAttached();
}



void Dwarf::getPositionOnScreen( SDL_Point *point ) {
	point->x = dstRect->x;
	point->y = dstRect->y;
}


void Dwarf::getPosition( SDL_Point *point ){
	point->x = dstRect->x - parentDst->x;
	point->y = dstRect->y - parentDst->y;
}


void Dwarf::getDstRectOnScreen( SDL_Rect *rect ){
	rect->x = dstRect->x;
	rect->y = dstRect->y;
	rect->w = dstRect->w;
	rect->h = dstRect->h;
}
void Dwarf::getDstRect( SDL_Rect *rect ){

	rect->x = dstRect->x - parentDst->x;
	rect->y = dstRect->y - parentDst->y;
	rect->w = dstRect->w;
	rect->h = dstRect->h;


}

void Dwarf::getSrcRect( SDL_Rect *rect )
{
	rect->x = srcRect->x;
	rect->y = srcRect->y;
	rect->w = srcRect->w;
	rect->h = srcRect->h;

}
void Dwarf::onTextureSet( void ){}

void Dwarf::setSrcRect( SDL_Rect *rect ){
	srcRect->h = rect->h;
	srcRect->w = rect->w;
	srcRect->x = rect->x;
	srcRect->y = rect->y;

	
}


void Dwarf::onModifierStop( char* name, Modifier::StopState state){}






