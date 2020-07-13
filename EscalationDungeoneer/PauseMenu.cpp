#include "PauseMenu.h"

PauseMenu::PauseMenu() : Menu() {
	setTitle("Paused");

	// Create the buttons of the pause menu

	resume = new Button(GameManager::SCREENWIDTH / 2 - 100, GameManager::SCREENHEIGHT / 2 - 95, 200, 30, "Resume Game");
	savegame = new Button(GameManager::SCREENWIDTH / 2 - 100, GameManager::SCREENHEIGHT / 2 - 55, 200, 30, "Save Game");
	loadgame = new Button(GameManager::SCREENWIDTH / 2 - 100, GameManager::SCREENHEIGHT / 2 - 15, 200, 30, "Load Game");
	optionsmenu = new Button(GameManager::SCREENWIDTH / 2 - 100, GameManager::SCREENHEIGHT / 2 + 25, 200, 30, "Settings");
	exitToMenu = new Button(GameManager::SCREENWIDTH / 2 - 100, GameManager::SCREENHEIGHT / 2 + 65, 200, 30, "Quit to Menu");
	quitgame = new Button(GameManager::SCREENWIDTH / 2 - 100, GameManager::SCREENHEIGHT / 2 + 105, 200, 30, "Quit to Desktop");

	resume->setForeground(GameManager::LGRAY);
	resume->setBackground(GameManager::DGRAY);
	resume->setHover(GameManager::BLACK, GameManager::GRAY);
	resume->setStroke(2, GameManager::Gray20);
	resume->setAction(GameManager::pushCommand,"M:CLOS:PAUSED");
	resume->setTooltip("Get back in there!", 12, GameManager::GOLD, GameManager::DGRAY);

	savegame->setForeground(GameManager::LGRAY);
	savegame->setBackground(GameManager::DGRAY);
	savegame->setHover(GameManager::BLACK, GameManager::GRAY);
	savegame->setStroke(2, GameManager::Gray20);
	loadgame->setAction(GameManager::pushCommand, "G:SAVE:SAVEGM");
	savegame->setTooltip("Save the current game.", 12, GameManager::GOLD, GameManager::DGRAY);

	loadgame->setForeground(GameManager::LGRAY);
	loadgame->setBackground(GameManager::DGRAY);
	loadgame->setHover(GameManager::BLACK, GameManager::GRAY);
	loadgame->setStroke(2, GameManager::Gray20);
	loadgame->setAction(GameManager::pushCommand, "M:LOAD:LOADGM");
	loadgame->setTooltip("Load another game. Your current game will be saved.", 12, GameManager::GOLD, GameManager::DGRAY);

	optionsmenu->setForeground(GameManager::LGRAY);
	optionsmenu->setBackground(GameManager::DGRAY);
	optionsmenu->setHover(GameManager::BLACK, GameManager::GRAY);
	optionsmenu->setStroke(2, GameManager::Gray20);
	optionsmenu->setAction(GameManager::pushCommand, "M:LOAD:SETTIN");
	optionsmenu->setTooltip("Change Audio, Video, and Game Settings", 12, GameManager::GOLD, GameManager::DGRAY);

	exitToMenu->setForeground(GameManager::LGRAY);
	exitToMenu->setBackground(GameManager::DGRAY);
	exitToMenu->setHover(GameManager::BLACK, GameManager::GRAY);
	exitToMenu->setStroke(2, GameManager::Gray20);
	exitToMenu->setAction(GameManager::pushCommand,"M:LOAD:__MAIN");
	exitToMenu->setTooltip("Quit to Main Menu. Your current game will be saved.", 12, GameManager::GOLD, GameManager::DGRAY);

	quitgame->setForeground(GameManager::LGRAY);
	quitgame->setBackground(GameManager::DGRAY);
	quitgame->setHover(GameManager::BLACK, GameManager::GRAY);
	quitgame->setStroke(2, GameManager::Gray20);
	quitgame->setAction(GameManager::setRunning);
	quitgame->setTooltip("Quit to Desktop. Your current game will be saved.", 12, GameManager::GOLD, GameManager::DGRAY);

	addComponent(resume);
	addComponent(savegame);
	addComponent(loadgame);
	addComponent(optionsmenu);
	addComponent(exitToMenu);
	addComponent(quitgame);
}

void PauseMenu::update() {
	__super::update();
}

void PauseMenu::clean() {
	__super::clean();
}

void PauseMenu::render() {
	__super::render();
}

void PauseMenu::pollEvents(SDL_Event* e) {
	__super::pollEvents(e);
}