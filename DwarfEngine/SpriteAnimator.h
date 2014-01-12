#pragma once
#include "modifier.h"
#include "Ease.h"
#include <queue>

using namespace std;

struct AnimationItem {
	int id;
	int duration;
	int loop; 
	int startFrame;
	int endFrame;
	EaseType easing;
};

struct SpriteSlice {
	int from;
	int length;
};

class SpriteAnimator :	public Modifier {
public:
	SpriteAnimator(void);
	~SpriteAnimator(void);
	void addAnimationItem(int id, int duration, int loop, int startFrame, int endFrame,	EaseType easing);
	virtual void onRender(Uint32 deltaTime);
	virtual void halt(void);
	virtual void onStop(void);
private:
	AnimationItem* currentAnimationItem;
	queue<AnimationItem*> animations;
	int loopCount;
};

