#include "CreditsMenu.h"

CreditsMenu::CreditsMenu() : Menu() {
	this->setTitle("Credits");
	
	back = new Button(GameManager::SCREENWIDTH - 400, GameManager::SCREENHEIGHT - 100, 200, 30, "Go Back");
	back->setForeground(GameManager::LGRAY);
	back->setBackground(GameManager::DGRAY);
	back->setHover(GameManager::BLACK, GameManager::GRAY);
	back->setStroke(2, GameManager::Gray20);
	back->setAction(GameManager::pushCommand, "M:LOAD:__LAST");
	back->setTooltip("Go back.", 12, GameManager::GOLD, GameManager::DGRAY);

	vestinius = new Sprite("banner_credits","assets/banner_wide.png", Vector2F(0, 0), Vector2F( 1299, 471 ), 0.4f);
	vestinius->setScale(0.4f);


	this->addSpacing(150);
	this->addText("Programming", 18);
	this->addText("Riley C. Payung", 13);
	this->addSpacing(50);
	this->addText("Concept Art & Level Design", 18);
	this->addText("Riley C. Payung", 13);
	this->addSpacing(50);
	this->addText("Music and Sounds", 18);
	this->addText("Riley C. Payung", 13);
	this->addSpacing(50);
	this->addText("Gameplay/Storyline", 18);
	this->addText("Riley C. Payung", 13);
	this->addSpacing(25);
	vestinius->setPosition((GameManager::SCREENWIDTH / 2) - vestinius->getScaledSize().X / 2, last);
	last = last + vestinius->getScaledSize().Y;
	this->addSpacing(25);
	this->addText("www.vestinius.games | www.vestinius.com/escdun", 13);
	setBackground(GameManager::DGRAY);

	addComponent(back);
}

void CreditsMenu::render() {
	__super::render();
	for (Text* s : this->paras) {
		s->render();
	}
	vestinius->render();
}

void CreditsMenu::clean() {
	__super::clean();
	vestinius->clean();
}

void CreditsMenu::update() {
	__super::update();
}

void CreditsMenu::addText(std::string message, int size) {
	Text* t = new Text(message, size, WNORMAL, GameManager::RARE,Vector2F(0, last), Vector2F(GameManager::SCREENWIDTH, 30));
	t->setCenter();
	t->setMiddle();
	last = last + 30;
	this->paras.push_back(t);
	t = nullptr;
}

void CreditsMenu::addSpacing(int amount) {
	last = last + amount;
}