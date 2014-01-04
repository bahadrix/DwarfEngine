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

	void setTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect);
	void setTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, 
		double* angle, SDL_Point* pivot, SDL_RendererFlip flip);
	void translateDelta(int dx, int dy);
	void translate(int x, int y);
	void translate(SDL_Point *destination);
	Dwarf* breed();
	void adopt(Dwarf* child);
	bool isInRect(int x, int y);
	void getPosition(SDL_Point *point);
	void getRectangle(SDL_Rect *rect);
	//Fired only if registered to window's listeners
	virtual void onMouseEvent(SDL_Event *event);
	std::string name;
	std::vector<Dwarf*> children;
private:
	
	void init(SDL_Renderer* renderer, Dwarf *parent);
	
	SDL_Texture* texture;
	SDL_Rect* srcRect;
	SDL_Rect* dstRect;
	double* angle;
	SDL_Point* pivot;
	SDL_RendererFlip flip;

	Dwarf *parent;
	
	std::vector<Modifier*> modifiers;

protected:
	SDL_Renderer* renderer;

friend class Modifier;

};

