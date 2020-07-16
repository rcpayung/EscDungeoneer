#include "SettingsMenu.h"

SettingsMenu::SettingsMenu() : Menu(){
	setTitle("Settings");

	back = new Button(GameManager::SCREENWIDTH - 400, GameManager::SCREENHEIGHT - 100, 200, 30, "Go Back");
	back->setForeground(GameManager::LGRAY);
	back->setBackground(GameManager::DGRAY);
	back->setHover(GameManager::BLACK, GameManager::GRAY);
	back->setStroke(2, GameManager::Gray20);
	back->setAction(GameManager::pushCommand, "M:LOAD:__LAST");
	back->setTooltip("Go back", 12, GameManager::GOLD, GameManager::DGRAY);
	this->setBackground(GameManager::DGRAY);

	addComponent(back);
}

void SettingsMenu::update() {
	__super::update();
}

void SettingsMenu::render() {
	__super::render();
}

void SettingsMenu::clean() {
	__super::clean();
}