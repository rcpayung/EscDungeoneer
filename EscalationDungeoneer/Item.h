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

enum class ItemType {
	UNSET,
	WEAPON,
	ARMOR,
	CONSUMABLE,
	MISC,
	GLYPH
};

enum class ArmorType {
	UNSET,
	HELMET,
	BODY,
	LEGS,
	BOOTS,
	SHIELD,
	GLOVES,
	RING,
	AMULET
};

enum class WeaponType {
	UNSET,
	GUN,
	BOW,
	SWORD,
	DAGGER,
	TH_KNIVES
};
enum class GlyphType {
	UNSET,
	SQUARE,
	PENTAGRAM,
	TRIANGLE
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
	int value, stacksize;
	Text* l_stack;
	bool stackable;
	std::string name;
	Rarity rarity;
	Tooltip* t;
	Statistics stats;
	ItemType type;
	ArmorType a_type;
	WeaponType w_type;
	GlyphType g_type;
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

	std::string getName();

	Statistics getstats();
	void setStats(Statistics stats);
	
	WeaponType getWType() {
		if (this->type == ItemType::WEAPON) {
			return w_type;
		}
		return WeaponType::UNSET;
	}
	ArmorType getAType() {
		if (this->type == ItemType::ARMOR) {
			return a_type;
		}
		return ArmorType::UNSET;
	}
	ItemType getType() {
		return this->type;
	}

	GlyphType getGType() {
		return this->g_type;
	}

	void setItemType(ItemType type);
	void setWeaponType(WeaponType type);
	void setArmorType(ArmorType type);
	
	void handleEvents(SDL_Event* e);


};

