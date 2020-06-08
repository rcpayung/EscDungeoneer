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
	Menu(SDL_Renderer* rd, int SCREENWIDTH, int SCREENHEIGHT, const char* title);
	void addComponent(UIComponent* c);
	void addComponent(Text* tex);
	void setTitle(const char* title);
	void render();
	void update();
	void clean();
	void pollEvents(SDL_Event* e);

};

