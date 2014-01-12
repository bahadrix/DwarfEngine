#pragma once
#include "modifier.h"
#include "Ease.h"
#include <queue>

using namespace std;

struct AnimationItem {
	Uint16 id;
	Uint16 duration;
	Uint16 loop; 
	Uint16 startFrame;
	int endFrame;
	EaseType easing;
};

struct SpriteSlice {
	Uint16 from;
	Uint16 length;
};

class SpriteAnimator :	public Modifier {
public:
	SpriteAnimator(void);
	~SpriteAnimator(void);
	void addAnimationItem(Uint16 id, Uint16 duration, Uint16 loop, Uint16 startFrame, int endFrame,	EaseType easing);
	virtual void onRender(Uint32 deltaTime);
	virtual void halt(void);
	virtual void onStop(void);
private:
	AnimationItem* currentAnimationItem;
	queue<AnimationItem*> animations;
	Uint16 loopCount;
};

