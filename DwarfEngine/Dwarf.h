#pragma once
#include <SDL.h>
#include <vector>
#include "Modifier.h"

class Dwarf
{
public:
	Dwarf();
	Dwarf(SDL_Renderer* renderer, Dwarf *parent = NULL);
	virtual ~Dwarf(void);
	void preRender(void);
	void render(void);
	void addModifier(Modifier* modifier);

	virtual void setTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double* angle = nullptr, SDL_Point* pivot = NULL, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);
	void translateDelta(int dx, int dy);

	Dwarf* breed();
	void adopt(Dwarf* child);
	bool isInRect(int x, int y);
	void getPositionOnScreen(SDL_Point *point);
	void getPosition(SDL_Point *point);
	void getDstRectOnScreen(SDL_Rect *rect);
	void getDstRect(SDL_Rect *rect);
	void getSrcRect(SDL_Rect *rect);
	void setSrcRect(SDL_Rect *rect);
	//Fired only if registered to window's listeners
	virtual void onMouseEvent(SDL_Event *event);
	std::string name;
	std::vector<Dwarf*> children;
	virtual void onTextureSet(void);
	virtual void onModifierStop(char* name, Modifier::StopState state);
	//Dwarves must be translated relatively to parent, not directly to the screen.
	void translateOnScreen(int x, int y);
	void translateOnScreen(SDL_Point *destination);
private:
	
	void init(SDL_Renderer* renderer, Dwarf *parent);
	
	SDL_Rect *parentDst; //on screen destination of parent, zero-fill if null
	SDL_Rect* srcRect;
	SDL_Rect* dstRect;
	double* angle;
	SDL_Point* pivot;
	SDL_RendererFlip flip;
	Dwarf *parent;
	std::vector<Modifier*> modifiers;

protected:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
friend class Modifier;

};

