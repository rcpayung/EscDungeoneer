#pragma once
#include "GameObject.h"

enum class Rarity {
	COMMON,
	UNCOMMON,
	RARE,
	VERY_RARE,
	LEGENDARY,
	GODLY
};

class Item : public GameObject {
private:
	static int ID;
	int value, stacksize;
	bool stackable;
	std::string name;
	Rarity rarity;
	Tooltip* t;
public:
	Item(std::string name, float scale, const char* spritepath);
	Item();
	void generateRarity(float modifier);
	void setRarity(Rarity rare);
	int getID();
	void update();
	void render();
	void clean();
	void handleEvents(SDL_Event* e);
};

