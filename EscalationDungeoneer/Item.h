#pragma once
#include "GameObject.h"
class Item : public GameObject {
private:
	static int ID;
	int value, stacksize;
	bool stackable;
public:
	Item(std::string name, float scale, const char* spritepath);
	void update();
	void render();
	void clean();
	void handleEvents(SDL_Event* e);
};

