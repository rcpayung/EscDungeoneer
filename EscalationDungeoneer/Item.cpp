#include "Item.h"

int Item::ID = 0;

Item::Item(std::string name, float scale, const char* spritepath) : GameObject(name, Vector2F{ 0,0 }, Sizer{ 48, 48 }, spritepath) {
	Item::ID++;

}

void Item::update() {

}

void Item::render() {
	__super::render();
}

void Item::clean() {
	
}

void Item::handleEvents(SDL_Event* e) {
	__super::handleEvents(e);
	switch (e->type) {
	case SDL_MOUSEMOTION:
		break;
	default:
		break;
	}
}

void Item::generateRarity(float modifier) {
	int generation = 1 + (rand() % 15000);

	if (generation >= 2000 && generation < 6000 * modifier) {
		this->rarity = Rarity::UNCOMMON;
	}
	else if (generation >= 6000 * modifier && generation < 10000 * modifier) {
		this->rarity = Rarity::RARE;
	}
	else if (generation >= 10000 * modifier && generation < 13000 * modifier) {
		this->rarity = Rarity::VERY_RARE;
	}
	else if (generation >= 13000 * modifier && generation < 14500 * modifier) {
		this->rarity = Rarity::LEGENDARY;
	}
	else if (generation >= 14500) {
		this->rarity = Rarity::GODLY;
	}
	else {
		rarity = Rarity::COMMON;
	}
	delete &generation;
}

void Item::setRarity(Rarity rare) {
	this->rarity = rare;
}

int Item::getID() {
	return this->ID;
}