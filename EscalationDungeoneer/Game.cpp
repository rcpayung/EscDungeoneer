#include "Game.h"
#include "GameManager.h"

Game::Game(const char *title, int w, int h, int flags) {

	// Initialize Steam API
	SteamAPI_Init() ? printf("Steam initialization complete\n") : printf("Steam init failed");

	// set the screen width and height:
	GameManager::SCREENWIDTH = w;
	GameManager::SCREENHEIGHT = h;

	// Intialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		// Create the window and renderer.
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GameManager::SCREENWIDTH, GameManager::SCREENHEIGHT, SDL_WINDOW_SHOWN);
		this->rd = SDL_CreateRenderer(win, -1, 0);

		if (win && rd) {
			std::cout << "Done Init." << std::endl;
		}

		// Set the rendering hints, this will change with the settings menu.

		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		SDL_SetRenderDrawBlendMode(rd, SDL_BLENDMODE_BLEND);
		
		/* SET WINDOW ICON */ {
			SDL_Surface* icon = IMG_Load("assets/appicon.bmp");
			SDL_SetWindowIcon(win, icon);
			SDL_FreeSurface(icon);
		}

		// Load True type font sdl package
		if (TTF_Init() == -1) {
			printf("Error: %s\n", SDL_GetError());
		}

		worldPort.x = 0;
		worldPort.y = 0;
		worldPort.w = GameManager::SCREENWIDTH;
		worldPort.h = GameManager::SCREENHEIGHT;

		WORLD = new Scene(rd, 0, "Sauresgald", 0, 0, 1000, 1000, GameManager::SCREENWIDTH, GameManager::SCREENHEIGHT, 1.0f);
		mainmenu = new MainMenu(rd, "assets/escalationDungeoneerBackground.png");
		pausemenu = new PauseMenu(rd, "Paused");
	}

}


Game::~Game() {
	cleanup();
}

bool Game::isRunning() {
	return GameManager::running;
}

void Game::update() {
	// Handle all game updates here.
	if (!GameManager::isPlaying) {
		// game is not active:
		if (activeScene != nullptr) {
			activeScene = nullptr;
			if (GameManager::paused) GameManager::Pause();
			mainmenu->update();
		}
		else {
			mainmenu->update();
		}
	}
	else {
		// game is active
		if (activeScene == nullptr) {
			// NEED TO GET THE ACTIVE SCENE AND DISPLAY IT HERE
			activeScene = WORLD; // Placeholder until command-version is created.
		}
		else {
			// active scene is not nullptr
			if (GameManager::paused) {
				// if we paused the game, update the pause menu.
				pausemenu->update();
			}
			else {
				// if were not paused, update the active scene.
				activeScene->update(GameManager::paused);
			}
		}
	}
}

void Game::render() {
	SDL_RenderClear(rd);
	SDL_RenderSetViewport(rd, &worldPort);
	// Render World Elements Here:

	if (!GameManager::isPlaying) {
		// if were not playing, we are in the menus, so render the menu
		mainmenu->render();
	}
	else {
		// if we are playing, if the active scene is not nullptr, we render the active scene.
		if (activeScene != nullptr) {
			activeScene->render();
			if (GameManager::paused) {
				// if we paused the game, we also render the pause menu.
				pausemenu->render();
			}
		}
	}
	SDL_SetRenderDrawColor(rd, 0,0,0, 255);
	SDL_RenderPresent(rd);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (GameManager::isPlaying) {
			// if were playing the game
			if (GameManager::paused) {
				// if were paused then poll the events of the pause menu.
				pausemenu->pollEvents(&event);
			}
			// If were not paused and the scene is active, then we poll the events of the scene.
			if (activeScene != nullptr) activeScene->pollevents(event);
		}
		else {
			// if were not playing, were in the menus so poll the events of the main menu.
			mainmenu->pollEvents(&event);
		}
		
		switch (event.type) {

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				break;

			case SDLK_END:
				GameManager::setDev();
				break;
			default:
				break;
			};
			break;

		case SDL_KEYUP:

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (activeScene != nullptr && GameManager::isPlaying) {
					GameManager::Pause();
				}
				break;
			default:
				break;
			};
			break;
		case SDL_QUIT:
			GameManager::setRunning();
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
	mainmenu->clean();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	SteamAPI_Shutdown();
}