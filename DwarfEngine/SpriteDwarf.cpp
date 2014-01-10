#include "stdafx.h"
#include "SpriteDwarf.h"


SpriteDwarf::SpriteDwarf(void) {
	animator = new SpriteAnimator();
	addModifier(animator);
	//animator->
}


SpriteDwarf::~SpriteDwarf(void) {
}

void SpriteDwarf::onTextureSet(void) {
	int w,h;
	SDL_QueryTexture(texture, NULL, NULL,&w, &h);
	SDL_Rect spriteSize;
	getSrcRect(&spriteSize);
	colCount = w/spriteSize.w; // column count
	rowCount = h/spriteSize.h; // row count
}

int SpriteDwarf::addAnimation( Uint16 start, Uint16 size ) {

	vector<SDL_Rect> animation;
	SDL_Rect spriteSize;
	getSrcRect(&spriteSize);
	
	SDL_Rect rect;
	rect.w = spriteSize.w;
	rect.h = spriteSize.h;
	
	int i,x,y;

	for(i = start; i < start + size; i++) {
		x = i % colCount;
		y = i / colCount;
		
		rect.x = spriteSize.w * x;
		rect.y = spriteSize.h * y;
	
		animation.push_back(rect);
	}

	animations.push_back(animation);
	/*
	printf("\nSize: (%d, %d)", rowCount, colCount);
	for(i=0; i < animation.size(); i++) {
		printf("\n(%d, %d, %d, %d)", animation.at(i).x, animation.at(i).y, animation.at(i).w, animation.at(i).h);
	}
	*/

	return animations.size() - 1;
}

int SpriteDwarf::addAnimation( SpriteSlice *slice ){
	return addAnimation(slice->from, slice->length);
}

void SpriteDwarf::playAnimation( Uint16 id, Uint16 duration, Uint16 loop /*= 0*/, Uint16 startFrame /*= 0*/, int endFrame /*= -1*/, EaseType ease /*= EaseType::LINEAR*/ ) {
	animator->addAnimationItem(id, duration, loop, startFrame, endFrame, ease);
	animator->start();
}