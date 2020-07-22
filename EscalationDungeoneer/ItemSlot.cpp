#include "ItemSlot.h"
ItemSlot::ItemSlot(int x, int y, int w, int h, float scale) : UIComponent(x,y,w,h,scale) {
	this->itemID = 0;
	this->dest = { x,y,w,h };
	this->border = { x - 2,y - 2,w + 4,h + 4 };
	this->inside = false;
	this->item = nullptr;
}

void ItemSlot::update() {
	__super::update();
	if (item != nullptr) {
		item->update();
	}
}

void ItemSlot::render() {
	SDL_SetRenderDrawColor(GameManager::rd, 45, 45, 45, 255);
	if (item != nullptr) {
		switch (item->getRarity()) {
		case Rarity::UNCOMMON:
			SDL_SetRenderDrawColor(GameManager::rd, GameManager::UNCOMMON.r, GameManager::UNCOMMON.g, GameManager::UNCOMMON.b, GameManager::UNCOMMON.a);
			break;
		case Rarity::RARE:
			SDL_SetRenderDrawColor(GameManager::rd, GameManager::RARE.r, GameManager::RARE.g, GameManager::RARE.b, GameManager::RARE.a);
			break;
		case Rarity::VERY_RARE:
			SDL_SetRenderDrawColor(GameManager::rd, GameManager::VERYRARE.r, GameManager::VERYRARE.g, GameManager::VERYRARE.b, GameManager::VERYRARE.a);
			break;
		case Rarity::LEGENDARY:
			SDL_SetRenderDrawColor(GameManager::rd, GameManager::LEGENDARY.r, GameManager::LEGENDARY.g, GameManager::LEGENDARY.b, GameManager::LEGENDARY.a);
			break;
		case Rarity::GODLY:
			SDL_SetRenderDrawColor(GameManager::rd, GameManager::GOLD.r, GameManager::GOLD.g, GameManager::GOLD.b, GameManager::GOLD.a);
			break;
		default:
			break;
		}
	}
	SDL_RenderFillRect(GameManager::rd, &border);
	if (inside) {
		SDL_SetRenderDrawColor(GameManager::rd, 20, 20, 20, 255);
		SDL_RenderFillRect(GameManager::rd, &dest);
	}
	else {
		SDL_SetRenderDrawColor(GameManager::rd, 40, 40, 40, 255);
		SDL_RenderFillRect(GameManager::rd, &dest);
	}
	
	SDL_SetRenderDrawColor(GameManager::rd, 0, 0, 0, 255);
}

void ItemSlot::renderItem() {
	if (item != nullptr) {
		item->render();
		if (inside) {
			item->showToolTip();
		}
	}
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