#pragma once
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "steam_api.h"
#include "Text.h"
#include "GameObject.h"

class Game {
private:
	bool running = false;
	SDL_Renderer* rd;
	SDL_Window* win;
	float tick;
	float FPS;
	float newX, newY, cameraMoveVelX, cameraMoveVelY;
	// View Ports and Camera
	SDL_Rect worldPort, UIViewPort, camera;
	Text* tex;
	GameObject* player;
public:
	Game(const char *title, int w, int h, int flags);
	~Game();

	bool isRunning();
	void update();
	void render();
	void handleEvents();
	void cleanup();
	void FPSis(float FPS);
};

