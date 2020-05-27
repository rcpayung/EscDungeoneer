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
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
		this->rd = SDL_CreateRenderer(win, -1, 0);
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

		tex = new Text(rd, "Hello World", 25, WBOLD, WHITE, Vector2F(250, 250), Vector2F());
		player = new GameObject(rd,"player",50,50,64,128,1.0f,"assets/player.png");
		player->addAnimation(100, 1, 0, 0, true);
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
	player->update(false);
	tick++;
}

void Game::render() {
	SDL_RenderClear(rd);
	SDL_RenderSetViewport(rd, &worldPort);
	// Render World Elements Here:

	player->render(0.0f);



	// UI ELEMENT RENDERER:
	SDL_RenderSetViewport(rd, &UIViewPort);
	// Render UI Elements here:

	tex->render();

	SDL_SetRenderDrawColor(rd, 0, 0, 0, 255);
	SDL_RenderPresent(rd);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
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
				running = false;
				break;
			case SDLK_w:
				player->playAnimation(0, false);
				break;
			case SDLK_a:
				break;
			case SDLK_s:
				break;
			case SDLK_d:
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

	tex->clean();
	player->clean();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	SteamAPI_Shutdown();
}

void Game::FPSis(float FPS) {
	this->FPS = FPS;
}