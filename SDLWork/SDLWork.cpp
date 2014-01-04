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

int _tmain(int argc, _TCHAR* argv[]) {
	

	try {
        Window::Init("Living Bunkies");
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
        Window::Quit();
        return -1;
    }

    //Load up an image and some text
    SDL_Texture *tx_img, *tx_msg, *tx_testbut;
    try {
        //Load the image
        std::string imgFile = "res/img/bg-grid-2.jpg";
        tx_img = Window::LoadImage(imgFile);

		tx_testbut = Window::LoadImage("res/img/testbut.png");

        //Load the font and message
        std::string fontFile = "res/fonts/science.ttf";
        std::string text = "Pointer Obssessed Sprite! by Bahadir";
        SDL_Color color = { 255, 255, 255 };
        tx_msg = Window::RenderText(text, fontFile, color, 24);
    }
    catch (const std::runtime_error &e){
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

	textPos.x = Window::Box().w / 2 - textPos.w/2;
	textPos.y = Window::Box().h / 2 - textPos.h/2;


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
	Window::registerMouseListener(testBut);
	SDL_Rect butPos = {100,100,0,0};
	
	SDL_QueryTexture(tx_testbut,NULL,NULL,&butPos.w, &butPos.h);


	testBut->setTexture(tx_testbut,NULL, &butPos);
	std::vector<Dwarf*> block = Dwarf::getRenderBlock(Window::eve);
	for(int i=0; i < block.size(); i++) {

		printf("%d. %s\n",i, block.at(i)->name.c_str());
	}

	//----


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
			// "Let's rock my handy dwarves!"
			Window::eve->render(); 
			Dwarf::getRenderBlock(Window::eve);
		Window::Present();
		
    }

    Window::Quit();




	return 0;
}


