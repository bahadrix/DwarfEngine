#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <memory>
#include <SDL.h>
#include "Dwarf.h"
#include <vector>

/**
*  Window management class, provides a simple wrapper around
*  the SDL_Window and SDL_Renderer functionalities
*/
class Window {
public:

    static void Init(std::string title = "Window");

    static void Quit();

    static void Draw(SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip = NULL,
                     float angle = 0.0, int xPivot = 0, int yPivot = 0,
                     SDL_RendererFlip flip = SDL_FLIP_NONE);

    static SDL_Texture* LoadImage(const std::string &file);

    static SDL_Texture* RenderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize);
    ///Clear the renderer
    static void Clear();
    ///Present the renderer, ie. update screen
    static void Present();
    ///Get the window's box
    static SDL_Rect Box();
	//Fired by SDL
	static void onMouseEvent(SDL_Event *event);
	//Register mouse listener
	static void registerMouseListener(Dwarf *dwarf);
	//Master dwarf
	static Dwarf *eve;
	


private:
    static std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> mWindow;
    static std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> mRenderer;
    static SDL_Rect mBox;
	static std::vector<Dwarf*> mouseListeners;
};

#endif