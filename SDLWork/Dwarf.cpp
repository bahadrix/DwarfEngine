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

	/*
	for(int c=0; c < children.size(); c++)
		children.at(c)->render();
	*/



}



void Dwarf::setTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect) {
	this->texture = texture;
	this->srcRect = srcRect;
	this->dstRect = dstRect;
	this->angle = nullptr;
	
}


void Dwarf::setTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double* angle, SDL_Point* pivot, SDL_RendererFlip flip) {
	setTexture(texture, srcRect, dstRect);
	this->angle = angle;
	this->pivot = pivot;
	this->flip = flip;

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
	
}

void Dwarf::translate( int x, int y ) {
	translateDelta(x - dstRect->x, y - dstRect->y);
}

void Dwarf::translate( SDL_Point *destination ) {
	translate(destination->x, destination->y);
}

void Dwarf::getPosition( SDL_Point *point ) {
	point->x = dstRect->x;
	point->y = dstRect->y;
}

void Dwarf::getRectangle( SDL_Rect *rect ){
	rect->x = dstRect->x;
	rect->y = dstRect->y;
	rect->w = dstRect->w;
	rect->h = dstRect->h;
}
