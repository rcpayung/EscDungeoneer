#pragma once
#include "UIComponent.h"
#include "Button.h"
#include "Text.h"
#include <iostream>
#include <vector>

class Menu {
private:
	std::vector<UIComponent*> options;
	std::vector<Text*> labels;
	SDL_Renderer* rd;
	int SCREENWIDTH, SCREENHEIGHT;
protected:
	
public:

	// Text Colors	  R   G   B
	SDL_Color WHITE{ 255,255,255, 255 };
	SDL_Color GREEN{ 100,200,100, 255 };
	SDL_Color LGRAY{ 200,200,200, 255 };
	SDL_Color L_BLU{ 20, 90,150, 255 };
	SDL_Color L_RED{ 150, 25, 25, 255 };
	SDL_Color GRAY{ 140,140,140, 255 };
	SDL_Color D_GRE{ 20, 50, 20, 255 };
	SDL_Color DGRAY{ 25, 25, 25, 255 };
	SDL_Color BLACK{ 0,  0,  0, 255 };

	Menu(SDL_Renderer* rd, int SCREENWIDTH, int SCREENHEIGHT);
	void addComponent(UIComponent* c);
	void addComponent(Text* tex);
	void setTitle(const char* title);
	void render();
	void update();
	void clean();
	void pollEvents(SDL_Event* e);

};

