#include "ArmorSlot.h"

ArmorSlot::ArmorSlot(int x, int y, int w, int h) : ItemSlot(x, y, w, h, GameManager::scale) {
	this->setAllowedItemType(ItemType::ARMOR);
}

void ArmorSlot::update() {
	__super::update();
}

void ArmorSlot::render() {
	__super::render();
	__super::renderItem();
}

void ArmorSlot::clean() {
	__super::clean();
}

void ArmorSlot::setItem(Item* item) {
	if (item == nullptr) {
		this->item = nullptr;
		return;
	}
	if (item->getType() == ItemType::ARMOR) {
		this->item = item;
		return;
	}
	else {
		printf("Item %s not armor or not correct armor type\n", item->getName().c_str());
	}
}

void ArmorSlot::handleEvents(SDL_Event* e) {
	__super::handleEvents(e);
}

ArmorType ArmorSlot::getAType() {
	return this->armortype;
}
void ArmorSlot::setArmorType(ArmorType t) {
	this->armortype = t;
}