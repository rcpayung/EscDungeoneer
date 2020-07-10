#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* rd, int SCREENWIDTH, int SCREENHEIGHT, const char * backgroundLoc) : Menu(rd,SCREENWIDTH,SCREENHEIGHT) {
	this->background = new Sprite(rd, backgroundLoc, 0, 0, 1920, 1080, 0.8f);
	play = new Button(rd, SCREENWIDTH - 400, SCREENHEIGHT - 300, 200, 30, "New Game");
	loadlast = new Button(rd, SCREENWIDTH - 400, SCREENHEIGHT - 260, 200, 30, "Continue");
	loadother = new Button(rd, SCREENWIDTH - 400, SCREENHEIGHT - 220, 200, 30, "Load Game");
	optionsmenu = new Button(rd, SCREENWIDTH - 400, SCREENHEIGHT - 180, 200, 30, "Settings");
	quit = new Button(rd, SCREENWIDTH - 400, SCREENHEIGHT - 140, 200, 30, "Exit Game");

	play->setForeground(BLACK);
	play->setBackground(LGRAY);
	play->setHover(GREEN, DGRAY);
	play->setStroke(2, GREEN);
	play->setAction(GameManager::setPlaying);
	play->setTooltip("Play a new game of Escalation Dungeoneer");

	loadlast->setForeground(BLACK);
	loadlast->setBackground(LGRAY);
	loadlast->setHover(GREEN, DGRAY);
	loadlast->setStroke(2, GREEN);
	loadlast->setTooltip("Resume your last game");

	loadother->setForeground(BLACK);
	loadother->setBackground(LGRAY);
	loadother->setHover(GREEN, DGRAY);
	loadother->setStroke(2, GREEN);
	loadother->setTooltip("Load a previous game");

	optionsmenu->setForeground(BLACK);
	optionsmenu->setBackground(LGRAY);
	optionsmenu->setHover(GREEN, DGRAY);
	optionsmenu->setStroke(2, GREEN);
	optionsmenu->setTooltip("Change Audio, Video, and Game Settings");

	quit->setForeground(BLACK);
	quit->setBackground(LGRAY);
	quit->setHover(GREEN, DGRAY);
	quit->setStroke(2, GREEN);
	quit->setAction(GameManager::setRunning);
	quit->setTooltip("Exit Escalation Dungeoneer");

	addComponent(play);
	addComponent(loadlast);
	addComponent(loadother);
	addComponent(optionsmenu);
	addComponent(quit);
}

void MainMenu::update() {
	__super::update();
}

void MainMenu::clean() {
	background->clean();
	__super::clean();
}

void MainMenu::render() {
	background->render(0.0f);
	__super::render();
}

void MainMenu::pollEvents(SDL_Event* e) {
	__super::pollEvents(e);
}