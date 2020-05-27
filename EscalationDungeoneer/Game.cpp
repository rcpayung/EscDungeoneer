#include "Game.h"

Game::Game(const char *title, int w, int h, int flags) {
	win = NULL;
	rd = NULL;


	if (SteamAPI_Init()) {
		printf("Steam initialization complete\n");
	}
	else {
		printf("Steam init failed");
	}


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Done Init." << std::endl;
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);
		this->rd = SDL_CreateRenderer(win, -1, 0);
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		this->running = true;
		/* SET WINDOW ICON */ {
			SDL_Surface* icon = IMG_Load("assets/appicon.bmp");
			SDL_SetWindowIcon(win, icon);
			SDL_FreeSurface(icon);
		}

		tick = 0;

		// World Elements Port
		worldPort.x = 0;
		worldPort.y = 0;
		worldPort.w = w;
		worldPort.h = h;
		// UI View Port
		UIViewPort.x = 0;
		UIViewPort.y = 0;
		UIViewPort.w = w;
		UIViewPort.h = h;
		// Camera

		if (TTF_Init() == -1) {
			printf("Error: %s\n", SDL_GetError());
		}

		// Text Colors	  R   G   B
		SDL_Color WHITE{ 255,255,255 };
		SDL_Color GREEN{ 100,200,100 };
		SDL_Color LGRAY{ 220,220,220 };
		SDL_Color L_BLU{  20, 90,150 };
		SDL_Color L_RED{ 150, 25, 25 };
		SDL_Color D_GRE{  20, 50, 20 };


		WORLD = new Scene(rd, 0, "Sauresgald", 0, 0, 1000, 1000, SCREENWIDTH, SCREENHEIGHT, 1.0f);
		activeScene = WORLD;
	}

}

Game::~Game() {
	cleanup();
}

bool Game::isRunning() {
	return running;
}

void Game::update() {
	// Handle all game updates here.
	
	if (activeScene != nullptr) {
		activeScene->update(paused);
	}

	tick++;
}

void Game::render() {
	SDL_RenderClear(rd);
	SDL_RenderSetViewport(rd, &worldPort);
	// Render World Elements Here:
	if (activeScene != nullptr) {
		activeScene->render();
	}


	// UI ELEMENT RENDERER:
	SDL_RenderSetViewport(rd, &UIViewPort);
	// Render UI Elements here:


	SDL_SetRenderDrawColor(rd, 100,100,100, 255);
	SDL_RenderPresent(rd);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (activeScene != nullptr) {
			activeScene->pollevents(event);
		}
		switch (event.type) {
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {
			default:
				break;
			};
			break;

		case SDL_KEYUP:

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:

				if (paused) paused = false;
				else paused = true;

				break;
			default:
				break;
			};
			break;

		case SDL_QUIT:
			running = false;
			break;

		default:
			break;
		}
	}
}

void Game::cleanup() {
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rd);

	WORLD->clean();

	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	SteamAPI_Shutdown();
}