#include "WeaponSlot.h"

WeaponSlot::WeaponSlot(int x, int y, int w, int h) : ItemSlot(x, y, w, h, GameManager::scale) {
	this->setAllowedItemType(ItemType::WEAPON);
}

void WeaponSlot::update() {
	__super::update();
}

void WeaponSlot::render() {
	__super::render();
	__super::renderItem();
}

void WeaponSlot::clean() {
	__super::clean();
}

void WeaponSlot::setItem(Item* item) {
	if (item == nullptr) {
		this->item = nullptr;
		return;
	}
	if (item->getType() == ItemType::WEAPON) {
		this->item = item;
		return;
	}
	else {
		printf("Item %s not weapon or not correct weapon type\n", item->getName().c_str());
	}
}

void WeaponSlot::handleEvents(SDL_Event* e) {
	__super::handleEvents(e);
}

WeaponType WeaponSlot::getWType() {
	return this->weapontype;
}
void WeaponSlot::setWeaponType(WeaponType t) {
	this->weapontype = t;
}