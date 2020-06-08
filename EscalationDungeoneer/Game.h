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


class Game {
private:
	SDL_Renderer* rd;
	SDL_Window* win;

	float tick;
	SDL_Rect worldPort;

	Scene* activeScene;
	std::vector<Scene*> scenes;
	Scene* WORLD;

	Button *exitbutton, *resume;
	Menu* pause;

	const int SCREENWIDTH = 1080;
	const int SCREENHEIGHT = 720;
public:
	static bool running;
	static bool paused;
	Game(const char *title, int w, int h, int flags);
	~Game();

	bool isRunning();
	void update();
	void render();
	void handleEvents();
	void cleanup();
	static void setRunning();
	static void Pause();
};

