#pragma once
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "steam_api.h"
#include "Text.h"
#include "GameObject.h"
#include "Scene.h"

class Game {
private:
	bool running = false, paused = false;
	SDL_Renderer* rd;
	SDL_Window* win;
	float tick;
	// View Ports and Camera
	SDL_Rect worldPort, UIViewPort;
	Scene* activeScene;
	std::vector<Scene*> scenes;
	Scene* WORLD;
	const int SCREENWIDTH = 1080;
	const int SCREENHEIGHT = 720;
public:
	Game(const char *title, int w, int h, int flags);
	~Game();

	bool isRunning();
	void update();
	void render();
	void handleEvents();
	void cleanup();
};

