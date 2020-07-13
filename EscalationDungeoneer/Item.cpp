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


