#pragma once
#include "Menu.h"
#include "GameManager.h"
class PauseMenu : public Menu {
private:
	Button* resume, * savegame, * loadgame, * optionsmenu, * exitToMenu, *quitgame;
protected:

public:
	PauseMenu();
	void update();
	void render();
	void clean();
	void pollEvents(SDL_Event* e);
};