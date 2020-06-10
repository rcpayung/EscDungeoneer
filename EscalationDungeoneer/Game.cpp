#include "Game.h"


bool Game::running = true;
bool Game::paused = false;

Game::Game(const char *title, int w, int h, int flags) {

	// Initialize Steam API
	if (SteamAPI_Init()) {
		printf("Steam initialization complete\n");
	}
	else {
		printf("Steam init failed");
	}

	// Intialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Done Init." << std::endl;
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);
		this->rd = SDL_CreateRenderer(win, -1, 0);
		
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


		tick = 0;

		worldPort.x = 0;
		worldPort.y = 0;
		worldPort.w = w;
		worldPort.h = h;

		// Text Colors	  R   G   B
		SDL_Color WHITE{ 255,255,255, 255 };
		SDL_Color GREEN{ 100,200,100, 255 };
		SDL_Color LGRAY{ 200,200,200, 255 };
		SDL_Color L_BLU{  20, 90,150, 255 };
		SDL_Color L_RED{ 150, 25, 25, 255 };
		SDL_Color GRAY { 140,140,140, 255 };
		SDL_Color D_GRE{  20, 50, 20, 255 };
		SDL_Color DGRAY{  25, 25, 25, 255 };
		SDL_Color BLACK{   0,  0,  0, 255 };

		WORLD = new Scene(rd, 0, "Sauresgald", 0, 0, 1000, 1000, SCREENWIDTH, SCREENHEIGHT, 1.0f);
		pause = new Menu(rd, SCREENWIDTH, SCREENHEIGHT,"Paused");
		mainmenu = new Menu(rd, SCREENWIDTH, SCREENHEIGHT, "MainMenu");

		resume = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 - 95, 200, 30, "Resume Game");
		savegame = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 - 55, 200, 30, "Save Game");
		loadgame = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 - 15, 200, 30, "Load Game");
		options = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 + 25, 200, 30, "Options");
		exitbutton = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 + 65, 200, 30, "Quit");

		resume->setForeground(BLACK);
		resume->setBackground(LGRAY);
		resume->setHover(GREEN, DGRAY);
		resume->setStroke(2, GREEN);
		resume->setAction(Game::Pause); // problem with this function. possibly even the menu class.
		pause->addComponent(resume);

		exitbutton->setForeground(BLACK);
		exitbutton->setBackground(LGRAY);
		exitbutton->setHover(GREEN, DGRAY);
		exitbutton->setStroke(2, GREEN);
		exitbutton->setAction(Game::setRunning);
		pause->addComponent(exitbutton);

		savegame->setForeground(BLACK);
		savegame->setBackground(LGRAY);
		savegame->setHover(GREEN, DGRAY);
		savegame->setStroke(2, GREEN);
		//savegame->setAction();
		pause->addComponent(savegame);

		loadgame->setForeground(BLACK);
		loadgame->setBackground(LGRAY);
		loadgame->setHover(GREEN, DGRAY);
		loadgame->setStroke(2, GREEN);
		//loadgame->setAction();
		pause->addComponent(loadgame);

		options->setForeground(BLACK);
		options->setBackground(LGRAY);
		options->setHover(GREEN, DGRAY);
		options->setStroke(2, GREEN);
		//options->setAction();
		pause->addComponent(options);

		activeScene = WORLD;
	}

}

void Game::setRunning() {
	!Game::running ? Game::running = true : Game::running = false;
}

void Game::Pause() {
	!Game::paused ? Game::paused = true : Game::paused = false;
}


Game::~Game() {
	cleanup();
}

bool Game::isRunning() {
	return Game::running;
}

void Game::update() {
	// Handle all game updates here.
	
	if (activeScene != nullptr) {
		activeScene->update(paused);
	}
	if (paused) {
		pause->update();
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


	// Render UI Elements here:
	if (paused) {
		pause->render();
	}
	SDL_SetRenderDrawColor(rd, 0,0,0, 255);
	SDL_RenderPresent(rd);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (activeScene != nullptr) {
			activeScene->pollevents(event);
		}
		if (paused) {
			pause->pollEvents(&event);
		}
		switch (event.type) {

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				
				break;
			default:
				break;
			};
			break;

		case SDL_KEYUP:

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (activeScene != nullptr) {
					Game::Pause();
				}
				break;
			default:
				break;
			};
			break;

		case SDL_QUIT:
			setRunning();
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