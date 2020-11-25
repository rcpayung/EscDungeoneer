#include "MainMenu.h"

MainMenu::MainMenu(const char * backgroundLoc) : Menu() {
	this->background = new Sprite("background",backgroundLoc, Vector2F(0, 0), Vector2F{ 1920, 1080 }, 0.8f);
	
	play = new Button(GameManager::SCREENWIDTH - 400, GameManager::SCREENHEIGHT - 300, 200, 30, "New Game");
	loadlast = new Button(GameManager::SCREENWIDTH - 400, GameManager::SCREENHEIGHT - 260, 200, 30, "Resume Last Game");
	loadother = new Button(GameManager::SCREENWIDTH - 400, GameManager::SCREENHEIGHT - 220, 200, 30, "Load Game");
	optionsmenu = new Button(GameManager::SCREENWIDTH - 400, GameManager::SCREENHEIGHT - 180, 200, 30, "Settings");
	credits = new Button(GameManager::SCREENWIDTH - 400, GameManager::SCREENHEIGHT - 140, 200, 30, "Credits");
	quit = new Button(GameManager::SCREENWIDTH - 400, GameManager::SCREENHEIGHT - 100, 200, 30, "Exit Game");
	
	
	dev_tE = new Button(200, GameManager::SCREENHEIGHT - 300, 200, 30, "Art Tile Editor");
	dev_bE = new Button(200, GameManager::SCREENHEIGHT - 260, 200, 30, "Logic Tile Editor");

	play->setForeground(GameManager::LGRAY);
	play->setBackground(GameManager::DGRAY);
	play->setHover(GameManager::BLACK, GameManager::GRAY);
	play->setStroke(2, GameManager::Gray20);
	play->setAction(GameManager::pushCommand,"G:LOAD:_NEWGM");
	play->setTooltip("Play a new game of Escalation Dungeoneer", 12, GameManager::GOLD, GameManager::DGRAY);

	loadlast->setForeground(GameManager::LGRAY);
	loadlast->setBackground(GameManager::DGRAY);
	loadlast->setHover(GameManager::BLACK, GameManager::GRAY);
	loadlast->setStroke(2, GameManager::Gray20);
	loadlast->setAction(GameManager::pushCommand, "G:LOAD:LASTGM");
	loadlast->setTooltip("Resume your last game", 12, GameManager::GOLD, GameManager::DGRAY);

	loadother->setForeground(GameManager::LGRAY);
	loadother->setBackground(GameManager::DGRAY);
	loadother->setHover(GameManager::BLACK, GameManager::GRAY);
	loadother->setStroke(2, GameManager::Gray20);
	loadother->setAction(GameManager::pushCommand, "G:LOAD:OTHEGM");
	loadother->setTooltip("Load a previous game", 12, GameManager::GOLD, GameManager::DGRAY);

	optionsmenu->setForeground(GameManager::LGRAY);
	optionsmenu->setBackground(GameManager::DGRAY);
	optionsmenu->setHover(GameManager::BLACK, GameManager::GRAY);
	optionsmenu->setStroke(2, GameManager::Gray20);
	optionsmenu->setAction(GameManager::pushCommand, "M:OPEN:SETTIN");
	optionsmenu->setTooltip("Change Audio, Video, and Game Settings",12, GameManager::GOLD, GameManager::DGRAY);

	credits->setForeground(GameManager::LGRAY);
	credits->setBackground(GameManager::DGRAY);
	credits->setHover(GameManager::BLACK, GameManager::GRAY);
	credits->setStroke(2, GameManager::Gray20);
	credits->setAction(GameManager::pushCommand, "M:OPEN:CREDIT");
	credits->setTooltip("Credits of Escalation Dungeoneer", 12, GameManager::GOLD, GameManager::DGRAY);

	quit->setForeground(GameManager::LGRAY);
	quit->setBackground(GameManager::DGRAY);
	quit->setHover(GameManager::BLACK, GameManager::GRAY);
	quit->setStroke(2, GameManager::Gray20);
	quit->setAction(GameManager::setRunning);
	quit->setTooltip("Exit Escalation Dungeoneer", 12, GameManager::GOLD, GameManager::DGRAY);

	dev_tE->setForeground(GameManager::LGRAY);
	dev_tE->setBackground(GameManager::DGRAY);
	dev_tE->setHover(GameManager::BLACK, GameManager::GRAY);
	dev_tE->setStroke(2, GameManager::Gray20);
	dev_tE->setAction(GameManager::pushCommand, "G:EDIT:ARTMAP");
	dev_tE->setTooltip("Edit the main world artistic tiles", 12, GameManager::GOLD, GameManager::DGRAY);

	dev_bE->setForeground(GameManager::LGRAY);
	dev_bE->setBackground(GameManager::DGRAY);
	dev_bE->setHover(GameManager::BLACK, GameManager::GRAY);
	dev_bE->setStroke(2, GameManager::Gray20);
	dev_bE->setAction(GameManager::pushCommand,"G:EDIT:LOGMAP");
	dev_bE->setTooltip("Edit the main world logical tiles", 12, GameManager::GOLD, GameManager::DGRAY);

	addComponent(play);
	addComponent(loadlast);
	addComponent(loadother);
	addComponent(optionsmenu);
	addComponent(credits);
	addComponent(quit);
}

void MainMenu::update() {
	__super::update();
	if (GameManager::devMode) {
		dev_tE->update();
		dev_bE->update();
	}
}

void MainMenu::clean() {
	background->clean();
	dev_tE->clean();
	dev_bE->clean();
	__super::clean();
}

void MainMenu::render() {
	background->render();
	if (GameManager::devMode) {
		dev_bE->render();
		dev_tE->render();
	}
	__super::render();
	
}

void MainMenu::pollEvents(SDL_Event* e) {
	__super::pollEvents(e);
	if (GameManager::devMode) {
		dev_tE->handleEvents(e);
		dev_bE->handleEvents(e);
	}
}