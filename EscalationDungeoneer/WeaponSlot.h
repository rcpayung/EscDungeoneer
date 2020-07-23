#pragma once
#include "ItemSlot.h"
class WeaponSlot : public ItemSlot {
private:
	WeaponType weapontype;
public:
	WeaponSlot(int x, int y, int w, int h);
	void update();
	void render();
	void clean();
	void handleEvents(SDL_Event* e);
	void setWeaponType(WeaponType t);
	WeaponType getWType();
	void setItem(Item* item);
};
