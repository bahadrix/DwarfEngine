#pragma once
#include "spritedwarf.h"
#include "Haulier.h"
#include "SpriteAnimator.h"
#include <queue>

#define TAG_CHARACTER_HAULIER "tag_char_haulier"

using namespace std;

//A character that moves 4 way
class CharacterFour : public SpriteDwarf {
public:
	static enum class Direction{VERTICAL, HORIZONTAL};
	int speed;
	SDL_Point focusPoint;
	CharacterFour(void);
	~CharacterFour(void);
	virtual void onModifierStop(char* name, Modifier::StopState state);
	virtual void setTexture(SpriteSlice upSlice, SpriteSlice downSlice, SpriteSlice leftSlice, SpriteSlice rightSlice, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double* angle = nullptr, SDL_Point* pivot = NULL, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);
	virtual void onMouseEvent(SDL_Event *event);
	void move(Direction direction, int delta, Uint16 duration, EaseType easing);
	void addPath(HaulierRoute *path);
	void followRoute(void);
	void breakMove(void);
	static CharacterFour* createFromMetaFile(const char* filePath);
private:
	Haulier *haulier;
	SpriteAnimator *animator;
	queue<HaulierRoute*> route;
};

