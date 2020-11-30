#pragma once
#include "GameManager.h"
#include "Menu.h"
#include "Armor.h"
#include "Weapon.h"
#include "Glyph.h"
#include "ItemSlot.h"
#include "Prompt.h"
#include "GlyphSlot.h"
#include "ArmorSlot.h"
#include "WeaponSlot.h"


class Inventory : public Menu {
private:
	std::vector<ItemSlot*> slots;
	bool showDetails = false;
	const int MAX_ITEMS = 70;
	int numItems;

	Text* itemCount;

	long coins;
	ItemSlot* selectedSlot;
	int selectedSlotID;
	void swapItems(ItemSlot* a);
	bool checkItem(ItemSlot* a);
	std::vector<SDL_Rect> borders;

	// EQUIPMENT
	ArmorSlot* head, /* neck,*/ * torso, * legs, * feet, * lefthand;
	ArmorSlot* leftring, * rightring;
	WeaponSlot* righthand;

	GlyphSlot* I_glyph_tri, * I_glyph_sqr, * I_glyph_PENT;
	Button* sort_alpha, * sort_by_id, * sort_by_rarity, * close, * help;

	Sprite* S_coins;
	
	SDL_Rect back;
	
	Prompt* prompt;
protected:
	
public:
	bool unequipShield();
	ItemSlot* findEmptySlot();
	Text* L_coins, * L_inv, * L_equip, * L_level;
	Inventory();
	bool removeItemAt(int index);
	bool pushItem(Item* item);
	void render() override;
	void update();
	void clean();
	bool closePrompt();
	void pollEvents(SDL_Event* e);
	bool loadGameInventory(const char* location);
	void sortinventory(std::string sort);
	void addCoins(long amount);
	void removeCoins(long amount);
};

