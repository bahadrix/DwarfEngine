// SDLWork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Window.h"
#include "Dwarf.h"
#include "SceneDirector.h"
#include "SceneObjects.h"
#include "SpriteDwarf.h"
#include "CharacterFour.h"

#include "Config.h"
#include <typeinfo>

Config *cfg;

void readConfig() {
	/*
	YAMLMapper *spriteMeta = new YAMLMapper();

	spriteMeta->parse("res/img/sprites.meta");
	*/
	cfg = new Config();
	printf("\nwidth: %d",cfg->window.width);
	

	

}

int _tmain(int argc, _TCHAR* argv[]) {
	readConfig();
	try {
        Window::Init(cfg->window.title);
    } catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
        Window::Quit();
        return -1;
    }

    //Load up an image and some text
    SDL_Texture *tx_img, *tx_msg, *tx_testbut, *tx_sprite;
    try {
        //Load the image
        std::string imgFile = "res/img/bg-grass.png";
        tx_img = Window::LoadImage(imgFile);

		tx_testbut = Window::LoadImage("res/img/testbut.png");
		tx_sprite = Window::LoadImage("res/img/bomba64.png");
        //Load the font and message
        std::string fontFile = "res/fonts/science.ttf";
        std::string text = "Pointer Obssessed Sprite! by Bahadir";
        SDL_Color color = { 255, 255, 255 };
        tx_msg = Window::RenderText(text, fontFile, color, 24);
    } catch (const std::runtime_error &e){
        //Catch error and crash
        std::cout << e.what() << std::endl;
        Window::Quit();
        return -1;
    }
    //Set a position to draw it with
    SDL_Rect pos = { Window::Box().w / 2 - 1920 / 2,
        Window::Box().h / 2 - 1080 / 2, 1920, 1080 };
    //The angle to draw at, so we can play with it

	SDL_Rect textPos;
	
	SDL_QueryTexture(tx_msg, NULL, NULL, &textPos.w, &textPos.h);

	textPos.x = 20;
	textPos.y = 20;


	//---
	
	SceneDirector *director = new SceneDirector();
	director->name = "Director";
	Window::eve->adopt(director);
	Window::registerMouseListener(director);

	Dwarf *background = director->breed();
	background->name = "Background";
	//eve->setTexture(msg, NULL, &textPos);
	background->setTexture(tx_img, NULL, &pos);

	Dwarf* texy = director->breed();
	texy->name = "Texy";
	texy->setTexture(tx_msg, NULL, &textPos);

	SignalButton* testBut = new SignalButton();
	testBut->name = "Test But";
	director->adopt(testBut);
	//Window::registerMouseListener(testBut);
	SDL_Rect butPos = {100,100,0,0};
	
	SDL_QueryTexture(tx_testbut,NULL,NULL,&butPos.w, &butPos.h);


	testBut->setTexture(tx_testbut,NULL, &butPos);
	SDL_Rect bombaSpriteSize = {0,0,64,64};
	SDL_Rect bombaGalDst = {250,300,64,64};
	/*
	SpriteDwarf *bombaGal = new SpriteDwarf();
	
	director->adopt(bombaGal);
	bombaGal->setTexture(tx_sprite,&bombaSpriteSize, &bombaGalDst);
	int goUp = bombaGal->addAnimation(0,4);
	bombaGal->playAnimation(0,700,0,0,0);
	//Window::registerMouseListener(bombaGal);
	*/

	CharacterFour *bombGal = new CharacterFour();
	SpriteSlice upSlice = {0U,4U};
	SpriteSlice downSlice = {11U,4U};
	SpriteSlice leftSlice = {15U,4U};
	SpriteSlice rightSlice = {4U,4U};
	
	bombGal->setTexture(upSlice, downSlice, leftSlice, rightSlice, tx_sprite, &bombaSpriteSize, &bombaGalDst);

	director->adopt(bombGal);
	Window::registerMouseListener(bombGal);
//tx_sprite, 0U, 4U, 12U, 4U, 16U, 4U, 5U,4U
	//--


    int angle = 0;
	
    //Our event structure
    SDL_Event e;
    //For tracking if we want to quit
    bool quit = false;
    while (!quit){
        //Event Polling
        while (SDL_PollEvent(&e)){
            //If user closes he window
            if (e.type == SDL_QUIT)
                    quit = true;
            //If user presses any key
            else if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
					//For rotating image
					case SDLK_d:
						//angle += 2;
						Window::eve->translateDelta(2,0);
						break;
					case SDLK_a:
						//angle -= 2;
						Window::eve->translateDelta(-2,0);
						break;
					//For quitting, escape key
					case SDLK_ESCAPE:
							quit = true;
							break;
					default:
							break;
				}
			} else if(
				e.type == SDL_MOUSEMOTION ||
				e.type == SDL_MOUSEBUTTONDOWN || 
				e.type == SDL_MOUSEBUTTONUP ||
				e.type == SDL_MOUSEWHEEL) {				
				Window::onMouseEvent(&e);
			} 	
        }
		//RENDERING
		Window::Clear();
		Window::render();
		Window::Present();	
    }
    Window::Quit();
	return 0;
}


