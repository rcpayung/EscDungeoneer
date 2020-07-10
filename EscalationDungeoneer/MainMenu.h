#pragma once
#include "Menu.h"
#include "GameManager.h"
class MainMenu : public Menu {
private:
	Button * play, * loadlast, * loadother, * optionsmenu, * credits, * quit;
	Button* dev_tE, * dev_bE;
	Sprite* background;
	Text* devModetext;
protected:

public:
	MainMenu(SDL_Renderer* rd, const char * backgroundLoc);
	void update();
	void render();
	void clean();
	void pollEvents(SDL_Event* e);
};

