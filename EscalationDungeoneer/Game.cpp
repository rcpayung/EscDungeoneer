#include "Game.h"

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
			icon = nullptr;
		}
		
	}
	else {
		throw nullptr;
	}
	worldPort = { 0,0,GameManager::SCREENWIDTH, GameManager::SCREENHEIGHT };

	WORLD = new Scene(0, "Sauresgald", 0, 0, 1000, 1000, 1.0f);
	mainmenu = new MainMenu("assets/escalationDungeoneerBackground.png");
	pausemenu = new PauseMenu();
	settings = new SettingsMenu();
	creditsmenu = new CreditsMenu();
	inventory = new Inventory();

	GameManager::pushCommand("M:LOAD:__MAIN");
	devModetext = new Text("DEV MODE ENABLED", 10, WBOLD, GameManager::GREEN, Vector2F(5, 15), Vector2F(150, 15));
	devModetext->setMiddle();
	version = new Text(GameManager::versionNum, 10, WBOLD, GameManager::GRAY, Vector2F(5,0), Vector2F(150, 15));
	version->setMiddle();
	timeElapsed = new Text("Time Elapsed (s): " + std::to_string(SDL_GetTicks()), 10, WBOLD, GameManager::GRAY, Vector2F(5, 30), Vector2F(150, 15));
	timeElapsed->setMiddle();


	this->object = new GameObject("Diamond", Vector2F(32, 32), Vector2F(64, 128));
	Sprite* sprite = new Sprite("Diamond", "assets/diamond.png", object->getPosition(), object->getSize(), 1.0f);
	object->pushSprite(sprite);
	Animation anim;
	anim.numFrames = 7;
	anim.startFrame = Vector2F(0, 0);
	anim.duration = 21;
	anim.loop = true;
	object->addAnimation(0, anim);
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
		else if (amenu == inventory) inventory->update();
	}
	if (GameManager::isPlaying && amenu == nullptr) {
		activeScene->update();
	}

	object->playAnimation(0, 0);
	object->update();

	std::srand((unsigned) SDL_GetTicks() * time(0));
	timeElapsed->setText("Time Elapsed (s): " + std::to_string(int(SDL_GetTicks()/1000)));
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
				else if (cargs.at(1) == "LASTGM") {
					// Load the last game.
					//loadGame("LAST");
					activeScene = WORLD;
					amenu = nullptr;
					GameManager::setPlaying();
				}

			}
			// GIVE COMMAND - GIVE THE PLAYER AN ITEM:
			else if (cargs.at(1) == "GIVE") {
				switch (std::stoi(cargs.at(2))) {
				Item* item;
				Statistics itemstats;
				case ITEMID::WORMSPTITER:
					item = new Item("Worm Spitter", 1.0f, "assets/wormspitter.png", false);
					item->generateRarity(1.0f);
					item->setItemType(ItemType::WEAPON);
					item->setWeaponType(WeaponType::GUN);
					item->setTooltip((item->getRarityString() + " Worm Spitter").c_str());
					itemstats = {25,25,25,25,25,25,25,25,2.5f}; // Placeholder.
					item->setStats(itemstats);
					inventory->pushItem(item);
					item = nullptr;
					break;
				case ITEMID::BLOODBONEPIKE:
					item = new Item("Bloodbone Pike", 1.0f, "assets/BloodbonePike.png", false);
					item->generateRarity(1.0f);
					item->setItemType(ItemType::WEAPON);
					item->setWeaponType(WeaponType::SWORD);
					item->setTooltip((item->getRarityString() + " Bloodbone Pike").c_str());
					itemstats = { 25,25,25,25,25,25,25,25,0.0f }; // Placeholder.
					item->setStats(itemstats);
					inventory->pushItem(item);
					item = nullptr;
					break;
				case ITEMID::WOODENSHIELD:
					item = new Item("Wooden Shield", 1.0f, "assets/woodenShield.bmp", false);
					item->generateRarity(1.0f);
					item->setItemType(ItemType::ARMOR);
					item->setArmorType(ArmorType::SHIELD);
					item->setTooltip((item->getRarityString() + " Wooden Shield").c_str());
					itemstats = { 25,25,25,25,25,25,25,25,0.0f }; // Placeholder.
					item->setStats(itemstats);
					inventory->pushItem(item);
					item = nullptr;
					break;
				default:
					break;
				}
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
					if (GameManager::editing) GameManager::editing = false;
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
				else if (cargs.at(2) == "INVENT" && !GameManager::onMain && !GameManager::paused) {
					lastmenu = amenu;
					amenu = inventory;
					GameManager::inInventory = true;
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
				else if (cargs.at(2) == "INVENT") {
					lastmenu = inventory;
					amenu = nullptr;
					inventory->closePrompt();
					GameManager::inInventory = false;
				}
				else if (cargs.at(2) == "INVPMT") {
					inventory->closePrompt();
				}
			}
			else if (cargs.at(1) == "SORT") {
				if (cargs.at(2) == "INBYID") {
					inventory->sortinventory("ID");
				}
				else if (cargs.at(2) == "INBYRR") {
					inventory->sortinventory("RARITY");
				}
				else if (cargs.at(2) == "INBYAL") {
					inventory->sortinventory("ALPHA");
				}
			}
		}
		else if (cargs.at(0) == "I") {
			if (cargs.at(1) == "delI") {
				int id = std::stoi(cargs.at(2));
				inventory->removeItemAt(id);
				inventory->closePrompt();
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
	object->render();
	if (amenu != nullptr) {
		if (amenu == mainmenu) mainmenu->render();
		else if (amenu == creditsmenu) creditsmenu->render();
		else if (amenu == pausemenu) pausemenu->render();
		else if (amenu == settings) settings->render();
		else if (amenu == inventory) inventory->render();
	}
	if (GameManager::devMode)
		devModetext->render();
	version->render();
	timeElapsed->render();
	SDL_RenderPresent(GameManager::rd);
	SDL_RenderClear(GameManager::rd);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (amenu != nullptr) {
			if (amenu == mainmenu) mainmenu->pollEvents(&event);
			else if (amenu == creditsmenu) creditsmenu->pollEvents(&event);
			else if (amenu == pausemenu) pausemenu->pollEvents(&event);
			else if (amenu == settings) settings->pollEvents(&event);
			else if (amenu == inventory) inventory->pollEvents(&event);
		}
		if (GameManager::isPlaying) {
			activeScene->pollevents(&event);
		}
		
		switch (event.type) {

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_e:
				// Open inventory.
				if (!GameManager::inInventory)
					GameManager::pushCommand("M:LOAD:INVENT");
				else
					GameManager::pushCommand("M:CLOS:INVENT");
				break;
			case SDLK_ESCAPE:
				if (GameManager::isPlaying) {
					if (!GameManager::inInventory) {
						!GameManager::paused ? GameManager::pushCommand("M:LOAD:PAUSED") : GameManager::pushCommand("M:CLOS:PAUSED");
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
	for (std::string i : GameManager::consoleLog) {
		printf("%s\n",i.c_str());
	}

	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(GameManager::rd);

	for (Scene* i : scenes) {
		i->clean();
	}
	scenes.clear();
	devModetext->clean();
	pausemenu->clean();
	mainmenu->clean();
	creditsmenu->clean();
	settings->clean();
	inventory->clean();
	WORLD->clean();
	version->clean();
	timeElapsed->clean();
	if (amenu != nullptr)
		amenu->clean();
	if (lastmenu != nullptr)
		lastmenu->clean();
	object->clean();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	//SteamAPI_Shutdown();
}