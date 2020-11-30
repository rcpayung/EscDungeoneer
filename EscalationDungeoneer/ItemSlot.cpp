#include "ItemSlot.h"
ItemSlot::ItemSlot(int x, int y, int w, int h, float scale) : UIComponent(x,y,w,h,scale) {
	this->itemID = 0;
	this->dest = { x,y,w,h };
	this->border = { x - 2,y - 2,w + 4,h + 4 };
	this->inside = false;
	this->item = nullptr;
	this->background = nullptr;
}

void ItemSlot::update() {
	__super::update();
	if (item != nullptr) {
		item->update();
	}
}

void ItemSlot::setBackground(const char* fileloc, int x, int y) {
	this->background = new Sprite("Background",fileloc, Vector2F(this->getPosition().X+8,this->getPosition().Y+8), Vector2F{ 32,32 },1.0f);
	this->background->setImage(Vector2F(x * background->getSize().X, y * background->getSize().Y));
}

void ItemSlot::render() {
	SDL_SetRenderDrawColor(GameManager::rd, 45, 45, 45, 255);
	if (item != nullptr) {
		switch (item->getRarity()) {
		case Rarity::UNCOMMON:
			GameManager::setDrawColor(GameManager::UNCOMMON);
			break;
		case Rarity::RARE:
			GameManager::setDrawColor(GameManager::RARE);
			break;
		case Rarity::VERY_RARE:
			GameManager::setDrawColor(GameManager::VERYRARE);
			break;
		case Rarity::LEGENDARY:
			GameManager::setDrawColor(GameManager::LEGENDARY);
			break;
		case Rarity::GODLY:
			GameManager::setDrawColor(GameManager::GODLY);
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
	
	if (background != nullptr && item == nullptr) {
		background->render();
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
	if (background != nullptr) {
		background->clean();
	}
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

ItemType ItemSlot::getAllowedItemType() {
	return this->type;
}

void ItemSlot::setAllowedItemType(ItemType t) {
	this->type = t;
}