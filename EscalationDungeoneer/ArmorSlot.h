#pragma once
#include "ItemSlot.h"
class ArmorSlot : public ItemSlot {
private:
	ArmorType armortype;
public:
	ArmorSlot(int x, int y, int w, int h);
	void update();
	void render();
	void clean();
	void handleEvents(SDL_Event* e);
	void setArmorType(ArmorType t);
	ArmorType getAType();
	void setItem(Item* item);
};

