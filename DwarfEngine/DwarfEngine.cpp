#include "stdafx.h"
#include <string>
#include <stdexcept>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

#include "DwarfEngine.h"
#include <queue>

//Initialize the unique_ptr's deleters here
std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> DwarfEngine::mWindow 
        = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> DwarfEngine::mRenderer
        = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
//Other static members
SDL_Rect DwarfEngine::mBox;
Dwarf *DwarfEngine::eve;
std::vector<Dwarf*> DwarfEngine::mouseListeners;
std::vector<Dwarf*> *DwarfEngine::renderQueue;
std::vector<Dwarf*>::iterator DwarfEngine::renderIterator;
std::queue<Dwarf*> DwarfEngine::que;

void DwarfEngine::Init(std::string title){
    //initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
                throw std::runtime_error("SDL Init Failed");
    if (TTF_Init() == -1)
                throw std::runtime_error("TTF Init Failed");
	
    //Setup our window size
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = 1000;
    mBox.h = 720;
    //Create our window
    mWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        mBox.w, mBox.h, SDL_WINDOW_SHOWN));
    //Make sure it created ok
    if (mWindow == nullptr)
        throw std::runtime_error("Failed to create window");

    //Create the renderer
    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    //Make sure it created ok
    if (mRenderer == nullptr)
        throw std::runtime_error("Failed to create renderer");
	DwarfEngine::eve = new Dwarf(mRenderer.get());
	DwarfEngine::eve->name = "Eve";
	renderQueue = new std::vector<Dwarf*>();
}
void DwarfEngine::Quit(){
    delete eve;
	TTF_Quit();
    SDL_Quit();
}
void DwarfEngine::Draw(SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle, 
                  int xPivot, int yPivot, SDL_RendererFlip flip)
{
    //Convert pivot pos from relative to object's top-left corner to be relative to its center
    xPivot += dstRect.w / 2;
    yPivot += dstRect.h / 2;
    //SDL expects an SDL_Point as the pivot location
    SDL_Point pivot = { xPivot, yPivot };
    //Draw the texture
    SDL_RenderCopyEx(mRenderer.get(), tex, clip, &dstRect, angle, &pivot, flip);
}
SDL_Texture* DwarfEngine::LoadImage(const std::string &file){
    SDL_Texture* tex = nullptr;
    tex = IMG_LoadTexture(mRenderer.get(), file.c_str());
    if (tex == nullptr)
        throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
    return tex;
}
SDL_Texture* DwarfEngine::RenderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize){
    //Open the font
    TTF_Font *font = nullptr;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr)
        throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
        
    //Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer.get(), surf);
    //Clean up unneeded stuff
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);

    return texture;
}
void DwarfEngine::Clear(){
    SDL_RenderClear(mRenderer.get());
}
void DwarfEngine::Present(){
    SDL_RenderPresent(mRenderer.get());
}
SDL_Rect DwarfEngine::Box(){
    //Update mBox to match the current window size
    SDL_GetWindowSize(mWindow.get(), &mBox.w, &mBox.h);
    return mBox;
}

void DwarfEngine::registerMouseListener( Dwarf *dwarf ) {
	mouseListeners.push_back(dwarf);
}

void DwarfEngine::onMouseEvent( SDL_Event *event ) {
	for(int i = 0; i < mouseListeners.size(); i++) {
		mouseListeners.at(i)->onMouseEvent(event);
	}
}

void DwarfEngine::render() {

	//Render by BFS

	que.push(eve);

	while(!que.empty()) {

		que.front()->render();
		for(renderIterator = que.front()->children.begin(); renderIterator != que.front()->children.end(); ++renderIterator) {
		//for(c = 0; c < que.front()->children.size(); c++ )
			que.push((*renderIterator));
		}
		que.pop();
	}

}