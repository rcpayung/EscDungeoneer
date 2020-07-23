#pragma once
#include "UIComponent.h"
#include "Item.h"
class ItemSlot : public UIComponent {
protected:
	int itemID;
	Item* item;
	SDL_Rect border;
	bool inside;
	ItemType type = ItemType::UNSET;
	Sprite* background;
public:
	ItemSlot(int x, int y, int w, int h, float scale);
	void setBackground(const char* fileloc, int x, int y);
	void update();
	void render();
	void renderItem();
	void clean();
	int getItemID();
	void setItemID(int id);
	Item* getItem();
	virtual void setItem(Item* item);
	void handleEvents(SDL_Event* e);
	ItemType getAllowedItemType();
	void setAllowedItemType(ItemType t);
};

