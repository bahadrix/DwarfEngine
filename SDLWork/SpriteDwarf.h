#pragma once
#include <SDL.h>
#include "dwarf.h"
#include <vector>
#include "Modifier.h"
#include "Ease.h"
#include "SpriteAnimator.h"
using namespace std;

class SpriteDwarf :	public Dwarf {
public:
	SpriteDwarf(void);
	~SpriteDwarf(void);
	void onTextureSet(void);
	int addAnimation(SpriteSlice *slice);
	int addAnimation(Uint16 start, Uint16 size);
	// loop: 0 infinite, endFrame : -1 lastFrame of animation
	void playAnimation(Uint16 id, Uint16 duration, Uint16 loop = 0, Uint16 startFrame = 0, int endFrame = -1, EaseType ease = EaseType::LINEAR);
private:
	SpriteAnimator *animator;
	Uint32 rowCount, colCount;
	vector< vector<SDL_Rect> > animations;

friend class SpriteAnimator;
	
};

