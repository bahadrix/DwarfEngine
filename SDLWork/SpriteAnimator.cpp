#include "stdafx.h"
#include "SpriteAnimator.h"
#include "SpriteDwarf.h"
#include <vector>

SpriteAnimator::SpriteAnimator(void) {
	loopCount = 0;
}


SpriteAnimator::~SpriteAnimator(void) {}

void SpriteAnimator::addAnimationItem( Uint16 id, Uint16 duration, Uint16 loop = 0, Uint16 startFrame = 0, int endFrame = -1, EaseType easing = EaseType::LINEAR) {
	AnimationItem *animation = new AnimationItem();
	animation->id = id;
	animation->duration = duration;
	animation->loop = loop;
	animation->startFrame = startFrame;
	animation->endFrame = endFrame;
	animation->easing;

	
	animations.push(animation);
}

void SpriteAnimator::onRender(Uint32 deltaTime){
	
	if(animations.empty()) {
		stop();
		return;
	}

	SpriteDwarf *dwarf = (SpriteDwarf*) target;
	currentAnimationItem = animations.front();
	vector<SDL_Rect> *frames = &dwarf->animations.at(currentAnimationItem->id);

	if(currentAnimationItem->endFrame == -1)
		currentAnimationItem->endFrame = frames->size() - 1;

	if(deltaTime >= currentAnimationItem->duration) 
		deltaTime = currentAnimationItem->duration;

	int frame = floor(Ease::get(
		currentAnimationItem->easing, 
		deltaTime, 
		currentAnimationItem->startFrame, 
		frames->size() - currentAnimationItem->startFrame, // extra wait for last frame
		currentAnimationItem->duration));

	if(frame > frames->size() - 1) // fix extra wait index issue
		frame = frames->size() - 1;

	dwarf->setSrcRect(&frames->at(frame));



	if(deltaTime == currentAnimationItem->duration) { //animation end
		loopCount++;
		if(loopCount == currentAnimationItem->loop) {
			dwarf->setSrcRect(&frames->at(currentAnimationItem->endFrame));
			animations.pop();
			loopCount = 0;
		}
		resetTimer();
	}
	

}

void SpriteAnimator::halt( void ) {
	stop();
	if(!animations.empty())
		std::queue<AnimationItem*>().swap(animations);
}

void SpriteAnimator::onStop(void) {
	if(currentAnimationItem != nullptr) {
		SpriteDwarf *dwarf = (SpriteDwarf*) target;
		vector<SDL_Rect> *frames = &dwarf->animations.at(currentAnimationItem->id);
		dwarf->setSrcRect(&frames->at(currentAnimationItem->endFrame));
	}
}