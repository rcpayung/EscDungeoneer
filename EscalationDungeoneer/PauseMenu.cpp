#include "PauseMenu.h"

PauseMenu::PauseMenu(SDL_Renderer* rd, int SCREENWIDTH, int SCREENHEIGHT, const char* title) : Menu(rd, SCREENWIDTH, SCREENHEIGHT) {
	this->setTitle(title);

	// Create the buttons of the pause menu

	resume = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 - 95, 200, 30, "Resume Game");
	savegame = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 - 55, 200, 30, "Save Game");
	loadgame = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 - 15, 200, 30, "Load Game");
	optionsmenu = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 + 25, 200, 30, "Settings");
	exitToMenu = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 + 65, 200, 30, "Quit to Menu");
	quitgame = new Button(rd, SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2 + 105, 200, 30, "Quit to Desktop");

	resume->setForeground(BLACK);
	resume->setBackground(LGRAY);
	resume->setHover(GREEN, DGRAY);
	resume->setStroke(2, GREEN);
	resume->setAction(GameManager::Pause);

	savegame->setForeground(BLACK);
	savegame->setBackground(LGRAY);
	savegame->setHover(GREEN, DGRAY);
	savegame->setStroke(2, GREEN);

	loadgame->setForeground(BLACK);
	loadgame->setBackground(LGRAY);
	loadgame->setHover(GREEN, DGRAY);
	loadgame->setStroke(2, GREEN);

	optionsmenu->setForeground(BLACK);
	optionsmenu->setBackground(LGRAY);
	optionsmenu->setHover(GREEN, DGRAY);
	optionsmenu->setStroke(2, GREEN);

	exitToMenu->setForeground(BLACK);
	exitToMenu->setBackground(LGRAY);
	exitToMenu->setHover(GREEN, DGRAY);
	exitToMenu->setStroke(2, GREEN);
	exitToMenu->setAction(GameManager::setPlaying);

	quitgame->setForeground(BLACK);
	quitgame->setBackground(LGRAY);
	quitgame->setHover(GREEN, DGRAY);
	quitgame->setStroke(2, GREEN);
	quitgame->setAction(GameManager::setRunning);

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