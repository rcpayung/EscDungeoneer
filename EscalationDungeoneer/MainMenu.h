#pragma once
#include "Menu.h"
#include "GameManager.h"
class MainMenu : public Menu {
private:
	Button * play, * loadlast, * loadother, * optionsmenu, * quit;
	Sprite* background;
protected:

public:
	MainMenu(SDL_Renderer* rd, int SCREENWIDTH, int SCREENHEIGHT, const char * backgroundLoc);
	void update();
	void render();
	void clean();
	void pollEvents(SDL_Event* e);
};

