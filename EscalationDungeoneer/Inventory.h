#pragma once
#include "GameManager.h"
#include "Menu.h"
#include "Armor.h"
#include "Weapon.h"
#include "Glyph.h"
#include "ItemSlot.h"


class Inventory : public Menu {
private:
	std::vector<Item*> items;
	std::vector<ItemSlot*> slots;
	std::vector<ItemSlot*> armorslots;
	const int MAX_ITEMS = 72;
	long coins;
	// EQUIPMENT
	Armor* head, * neck, * cape, * torso, * legs, * feet, * lefthand;
	Armor* leftring, * rightring;
	Weapon* righthand;
	// GLYPHS
	Glyph* triangle, * square, * diamond;
	
	Button* sort_alpha, * sort_by_id, * close, * help;
	Sprite* S_coins, * S_glyph1, * S_glyph2, * S_glyph3, * S_equipback, * S_invback;
	Text* L_coins, * L_inv, * L_equip, * L_level;
	SDL_Rect back;
protected:
	
public:
	Inventory();
	bool pushItem(Item* item);
	void render() override;
	void update();
	void clean();
	void pollEvents(SDL_Event* e);
	bool loadGameInventory(const char* location);
	void sortinventory(std::string sort);
	void addCoins(long amount);
	void removeCoins(long amount);
};

