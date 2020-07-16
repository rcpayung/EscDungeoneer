#include "ItemSlot.h"
ItemSlot::ItemSlot(int x, int y, int w, int h, float scale) : UIComponent(x,y,w,h,scale) {
	this->itemID = 0;
}

void ItemSlot::update() {
	__super::update();
	border = { dest.x - 2, dest.y - 2, dest.w + 4, dest.h + 4 };
}

void ItemSlot::render() {
	SDL_SetRenderDrawColor(GameManager::rd, 45, 45, 45, 255);
	SDL_RenderFillRect(GameManager::rd, &border);
	if (inside) {
		SDL_SetRenderDrawColor(GameManager::rd, 20, 20, 20, 255);
		SDL_RenderFillRect(GameManager::rd, &dest);
	}
	else {
		SDL_SetRenderDrawColor(GameManager::rd, 40, 40, 40, 255);
		SDL_RenderFillRect(GameManager::rd, &dest);
	}
	if (item != nullptr) {
		item->render();
	}
	SDL_SetRenderDrawColor(GameManager::rd, 0, 0, 0, 255);
}

void ItemSlot::clean() {
	__super::clean();
}

int ItemSlot::getItemID() {
	return this->itemID;
}

Item* ItemSlot::getItem() {
	return this->item;
}

void ItemSlot::setItem(Item* item) {
	this->item = item;
}

void ItemSlot::setItemID(int id) {
	this->itemID = id;
}


void ItemSlot::handleEvents(SDL_Event* e) {
	switch (e->type) {
	case SDL_MOUSEMOTION:
		if (GameManager::mx > this->getPosition().X&& GameManager::mx < (this->getPosition().X + this->getSize().X)
			&& GameManager::my > this->getPosition().Y&& GameManager::my < (this->getPosition().Y + this->getSize().Y)) {
			inside = true;
		}
		else {
			inside = false;
		}
		break;
	default:
		break;
	}
}