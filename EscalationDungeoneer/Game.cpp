#include "Game.h"
#include "GameManager.h"

Game::Game(const char *title, int w, int h, int flags) {

	// Initialize Steam API
	//SteamAPI_Init() ? printf("Steam initialization complete\n") : printf("Steam init failed");

	// set the screen width and height:
	GameManager::SCREENWIDTH = w;
	GameManager::SCREENHEIGHT = h;
	amenu = nullptr;
	lastmenu = nullptr;
	activeScene = nullptr;

	// Intialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		// Create the window and renderer.
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GameManager::SCREENWIDTH, GameManager::SCREENHEIGHT, SDL_WINDOW_SHOWN);
		
		// Create the renderer (Static: see GameManager.h).
		GameManager::rd = SDL_CreateRenderer(win, -1, 0);

		if (win && GameManager::rd) {
			std::cout << "Done Init." << std::endl;
		}
		// Load True type font sdl package
		if (TTF_Init() == -1) {
			printf("Error: %s\n", SDL_GetError());
		}

		// Set the rendering hints, this will change with the settings menu.
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		SDL_SetRenderDrawBlendMode(GameManager::rd, SDL_BLENDMODE_BLEND);
		
		/* SET WINDOW ICON */ {
			SDL_Surface* icon = IMG_Load("assets/appicon.bmp");
			SDL_SetWindowIcon(win, icon);
			SDL_FreeSurface(icon);
		}

		

		worldPort.x = 0;
		worldPort.y = 0;
		worldPort.w = GameManager::SCREENWIDTH;
		worldPort.h = GameManager::SCREENHEIGHT;

		WORLD = new Scene(0, "Sauresgald", 0, 0, 1000, 1000, 1.0f);
		mainmenu = new MainMenu("assets/escalationDungeoneerBackground.png");
		pausemenu = new PauseMenu();
		settings = new SettingsMenu();
		creditsmenu = new CreditsMenu();

		GameManager::pushCommand("M:LOAD:__MAIN");
		devModetext = new Text("dev Mode Enabled", 10, WBOLD, GameManager::GREEN, Vector2F(10, 10), Vector2F(50, 15));
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
	processCommands();
	SDL_GetMouseState(&GameManager::mx, &GameManager::my);
	if (amenu != nullptr) {
		if (amenu == mainmenu) mainmenu->update();
		else if (amenu == creditsmenu) creditsmenu->update();
		else if (amenu == pausemenu) pausemenu->update();
		else if (amenu == settings) settings->update();
	}
	if (GameManager::isPlaying) {
		activeScene->update();
	}

}

/*
Command Handler. This will process all commands sent to it via buttons or triggers.
*/
void Game::processCommands() {
	for (std::string command : GameManager::commands) {
		// process commands
		cargs.push_back(command.substr(0, 1));
		cargs.push_back(command.substr(2, 4));
		cargs.push_back(command.substr(7, 6));

		printf("%s:%s:%s\n", cargs.at(0).c_str(), cargs.at(1).c_str(), cargs.at(2).c_str());
	
		if (cargs.at(0) == "G") {
			if (cargs.at(1) == "LOAD") {
				if (cargs.at(2) == "_NEWGM") {
					this->amenu = nullptr;
					this->activeScene = WORLD;
					GameManager::setPlaying();
				}
			}
			else if (cargs.at(1) == "LASTGM") {
				// Load the last game.
				//loadGame("LAST");
				activeScene = WORLD;
				amenu = nullptr;
				GameManager::setPlaying();
			}
			else if (cargs.at(1) == "EDIT") {
				if (cargs.at(2) == "ARTMAP") {
					GameManager::setPlaying();
					GameManager::setEditing();
					amenu = nullptr;
					activeScene = WORLD;
					//edit = new Editor(&WORLD,"Art");
				}
				if (cargs.at(2) == "LOGMAP") {
					GameManager::setPlaying();
					GameManager::setEditing();
					amenu = nullptr;
					activeScene = WORLD;
					//edit = new Editor(&WORLD,"logic");
				}
			}
			else if (cargs.at(1) == "EXIT") {
				if (cargs.at(2) == "__MAIN") {
					GameManager::setPlaying();
					if (GameManager::editing) GameManager::editing = false;
					if (GameManager::paused) GameManager::Pause();
					amenu = mainmenu;
				}
				else if (cargs.at(2) == "__DESK") {
					GameManager::setRunning();
				}
			}
			// END OF "G"
		}
		else if (cargs.at(0) == "M") {
			// MENUS
			// LOAD COMMAND (OPEN)
			if (cargs.at(1) == "LOAD" || cargs.at(1) == "OPEN") {
				if (cargs.at(2) == "SETTIN") {
					GameManager::inSettings = true;
					this->lastmenu = amenu;
					this->amenu = settings;
				}
				else if (cargs.at(2) == "PAUSED") {
					this->lastmenu = nullptr;
					this->amenu = pausemenu;
					GameManager::Pause();
				}
				else if (cargs.at(2) == "__MAIN") {
					if (GameManager::isPlaying) GameManager::setPlaying();
					if (GameManager::paused) GameManager::Pause();
					this->lastmenu = nullptr;
					this->amenu = mainmenu;
				}
				// LOADS THE LAST MENU ON THE SCREEN. CAN BE NULLPTR
				else if (cargs.at(2) == "__LAST") {
					amenu = lastmenu;

					// This needs some work
				}
				else if (cargs.at(2) == "CREDIT") {
					lastmenu = amenu;
					amenu = creditsmenu;
				}
				
			}
			// CLOSE COMMAND
			else if (cargs.at(1) == "CLOS") {
				if (cargs.at(2) == "SETTIN") {
					GameManager::inSettings = false;
					GameManager::isPlaying ? amenu = pausemenu : amenu = mainmenu; 
					// If playing, change to the pause menu, if not, return to main menu.
				}
				else if (cargs.at(2) == "PAUSED") {
					GameManager::Pause();
					amenu = nullptr;
				}

			}
		}


		cargs.clear();
	}
	GameManager::commands.clear();
}

void Game::render() {
	SDL_RenderClear(GameManager::rd);
	SDL_RenderSetViewport(GameManager::rd, &worldPort);
	// Render World Elements Here:

	if (GameManager::isPlaying) {
		if (activeScene != nullptr)
			activeScene->render();
	}
	if (amenu != nullptr) {
		if (amenu == mainmenu) mainmenu->render();
		else if (amenu == creditsmenu) creditsmenu->render();
		else if (amenu == pausemenu) pausemenu->render();
		else if (amenu == settings) settings->render();
	}
	if (GameManager::devMode)
		devModetext->render();

	SDL_SetRenderDrawColor(GameManager::rd, 0,0,0, 255);
	SDL_RenderPresent(GameManager::rd);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (amenu != nullptr) {
			if (amenu == mainmenu) mainmenu->pollEvents(&event);
			else if (amenu == creditsmenu) creditsmenu->pollEvents(&event);
			else if (amenu == pausemenu) pausemenu->pollEvents(&event);
			else if (amenu == settings) settings->pollEvents(&event);
		}
		if (GameManager::isPlaying) {
			activeScene->pollevents(event);
		}
		
		switch (event.type) {

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (GameManager::isPlaying) {
					if (!GameManager::paused) {
						GameManager::pushCommand("M:LOAD:PAUSED");
					}
					else {
						GameManager::pushCommand("M:CLOS:PAUSED");
					}
				}
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
				break;
			default:
				break;
			};
			break;
		case SDL_QUIT:
			GameManager::pushCommand("G:EXIT:__DESK");
			break;

		default:
			break;
		}
	}
}

void Game::cleanup() {
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(GameManager::rd);

	amenu->clean();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	//SteamAPI_Shutdown();
}