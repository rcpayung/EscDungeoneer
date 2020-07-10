#pragma once
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "steam_api.h"
#include "Text.h"
#include "GameObject.h"
#include "Scene.h"
#include "Button.h"
#include "Menu.h"
#include "MainMenu.h"
#include "PauseMenu.h"


class Game {
private:
	SDL_Renderer* rd; // renderer, render all elements to this
	SDL_Window* win; // window, this is what the renderer renders to

	SDL_Rect worldPort;	// this is the viewport

	std::string ascene;
	Scene* activeScene; // Currently active scene.
	std::vector<Scene*> scenes; // Scene archive.
	Scene* WORLD; // World scene

	Button *exitbutton, *resume, *savegame, *loadgame, *options; // menu buttons.
	PauseMenu* pausemenu; // menus
	MainMenu *mainmenu;

public:

	Game(const char *title, int w, int h, int flags);
	~Game();

	bool isRunning();
	void update();
	void render();
	void handleEvents();
	void cleanup();
};

