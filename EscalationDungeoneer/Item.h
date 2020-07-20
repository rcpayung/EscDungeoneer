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

struct Statistics { /*MODIFIERS*/
	short MP; // MP
	short HP; // HP
	short ATT; // Attack
	short DEF; // Defense
	short DEX; // Dexterity
	short VIT; // Vitality
	short WIS; // Wisdom
	short VIS; // Visibility
	float SPD; // Speed
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
	Statistics stats;
public:
	Item(std::string name, float scale, const char* spritepath, bool stackable);
	Item();
	void setTooltip(std::string message);
	void showToolTip();

	void update();
	void render();
	void clean();

	void setPosition(Vector2F p);
	void setPosition(int x, int y);

	int getStack();
	void increase_stack(int amount);
	bool is_stackable();

	Rarity getRarity();
	std::string getRarityString();
	void generateRarity(float modifier);
	void setRarity(Rarity rare);

	int getID();

	std::string getName();

	Statistics getstats();
	void setStats(Statistics stats);
	void handleEvents(SDL_Event* e);
};

