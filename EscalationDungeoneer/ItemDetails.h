#pragma once
#include "UIComponent.h"
#include "Item.h"
class ItemDetails : public UIComponent {
private:
	Item* item;
	std::vector<Text*> stats;
	Text* drag;
	Text* name;
	SDL_Rect border;
	int lasty;
public:
	ItemDetails(int x, int y, int w, int h);
	void setItem(Item* item);
	void render();
	void update();
	void clean();
	void handleEvents(SDL_Event* e);

};

