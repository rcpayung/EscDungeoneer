#pragma once
#include "UIComponent.h"
#include "Item.h"
class ItemSlot : public UIComponent {
private:
	int itemID;
	Item* item;
	SDL_Rect border;
	bool inside;
public:
	ItemSlot(int x, int y, int w, int h, float scale);
	void update();
	void render();
	void clean();
	int getItemID();
	void setItemID(int id);
	Item* getItem();
	void setItem(Item* item);
	void handleEvents(SDL_Event* e);
};

