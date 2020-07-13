#pragma once
#include "UIComponent.h"
#include "Button.h"
#include "Text.h"
#include <iostream>
#include <vector>
#include "GameManager.h"

class Menu {
private:
	std::vector<UIComponent*> options;
	std::vector<Text*> labels;
	bool drawBackground = false;
	SDL_Color color;
	SDL_Rect screen;
protected:
public:
	Menu();
	void setBackground(SDL_Color color);
	void addComponent(UIComponent* c);
	void addComponent(Text* tex);
	void setTitle(const char* title);
	void render();
	void update();
	void clean();
	void pollEvents(SDL_Event* e);

};

