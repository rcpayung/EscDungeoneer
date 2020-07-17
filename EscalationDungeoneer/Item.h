#pragma once
#include "GameObject.h"
#include <iostream>
#include <stdio.h>

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
	Text* l_stack;
	bool stackable;
	std::string name;
	Rarity rarity;
	Tooltip* t;
public:
	Item(std::string name, float scale, const char* spritepath, bool stackable);
	Item();
	void setTooltip(std::string message);
	void showToolTip();
	void generateRarity(float modifier);
	void setRarity(Rarity rare);
	int getID();
	void update();
	void render();
	bool is_stackable();
	int getStack();
	void increase_stack(int amount);
	void clean();
	Rarity getRarity();
	std::string getRarityString();
	void handleEvents(SDL_Event* e);
	std::string getName();
};

