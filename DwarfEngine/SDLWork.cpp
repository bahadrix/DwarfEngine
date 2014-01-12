// SDLWork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "DwarfEngine.h"
#include "Dwarf.h"
#include "SceneDirector.h"
#include "SceneObjects.h"
#include "SpriteDwarf.h"
#include "CharacterFour.h"

#include "Config.h"
#include <typeinfo>

Config *cfg;

void readConfig() {
	
	YAMLMapper *spriteMeta = new YAMLMapper();

	SDL_Point spriteSize;
	spriteMeta->addMapping("sprite:cell_size", &spriteSize.x, 0);
	spriteMeta->addMapping("sprite:cell_size", &spriteSize.y, 1);

	spriteMeta->parse("res/img/sprites.meta");
	
	cfg = new Config();
	printf("\nwidth: %d",cfg->window.width);

}

int _tmain(int argc, _TCHAR* argv[]) {
	readConfig();
	try {
        DwarfEngine::Init(cfg->window.title);
    } catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
        DwarfEngine::Quit();
        return -1;
    }

    //Load up an image and some text
    SDL_Texture *tx_img, *tx_msg, *tx_testbut;
    try {
        //Load the image
        std::string imgFile = "res/img/bg-grass.png";
        tx_img = DwarfEngine::LoadImage(imgFile);

		tx_testbut = DwarfEngine::LoadImage("res/img/testbut.png");
        //Load the font and message
        std::string fontFile = "res/fonts/science.ttf";
        std::string text = "Pointer Obssessed Sprite! by Bahadir";
        SDL_Color color = { 255, 255, 255 };
        tx_msg = DwarfEngine::RenderText(text, fontFile, color, 24);
    } catch (const std::runtime_error &e){
        //Catch error and crash
        std::cout << e.what() << std::endl;
        DwarfEngine::Quit();
        return -1;
    }
    //Set a position to draw it with
    SDL_Rect pos = { DwarfEngine::Box().w / 2 - 1920 / 2,
        DwarfEngine::Box().h / 2 - 1080 / 2, 1920, 1080 };
    //The angle to draw at, so we can play with it

	SDL_Rect textPos;
	
	SDL_QueryTexture(tx_msg, NULL, NULL, &textPos.w, &textPos.h);

	textPos.x = 20;
	textPos.y = 20;


	//---
	
	SceneDirector *director = new SceneDirector();
	director->name = "Director";
	DwarfEngine::eve->adopt(director);
	DwarfEngine::registerMouseListener(director);

	Dwarf *background = director->breed();
	background->name = "Background";
	//eve->setTexture(msg, NULL, &textPos);
	background->setTexture(tx_img, NULL, &pos);

	Dwarf* texy = director->breed();
	texy->name = "Texy";
	texy->setTexture(tx_msg, NULL, &textPos);

	CharacterFour *bombGal = CharacterFour::createFromMeta("res/img/char4.bombagal.meta");
	
	bombGal->name = "BombaGal";
	director->adopt(bombGal);
	DwarfEngine::registerMouseListener(bombGal);
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
						DwarfEngine::eve->translateDelta(2,0);
						break;
					case SDLK_a:
						//angle -= 2;
						DwarfEngine::eve->translateDelta(-2,0);
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
				DwarfEngine::onMouseEvent(&e);
			} 	
        }
		//RENDERING
		DwarfEngine::Clear();
		DwarfEngine::render();
		DwarfEngine::Present();	
    }
    DwarfEngine::Quit();
	return 0;
}


