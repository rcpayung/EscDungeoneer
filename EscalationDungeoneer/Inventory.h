#pragma once
#include "GameManager.h"
#include "Menu.h"
#include "Armor.h"
#include "Weapon.h"
#include "Glyph.h"
#include "ItemSlot.h"


class Inventory : public Menu {
private:
	std::vector<ItemSlot*> slots;
	std::vector<ItemSlot*> armorslots;
	const int MAX_ITEMS = 72;
	int numItems;
	long coins;

	// EQUIPMENT
	Armor* head, * neck, * cape, * torso, * legs, * feet, * lefthand;
	Armor* leftring, * rightring;
	Weapon* righthand;
	Item* item;
	// GLYPHS
	Glyph* triangle, * square, * diamond;
	ItemSlot* I_glyph_tri, * I_glyph_sqr, * I_glyph_PENT;
	Button* sort_alpha, * sort_by_id, * sort_by_rarity, * close, * help;
	Sprite* S_coins, * S_glyphPENT_bg, * S_glyphTRI_bg, * S_glyphSQR_bg, * S_equipback, * S_invback;
	SDL_Rect back;

protected:
	
public:
	Text* L_coins, * L_inv, * L_equip, * L_level;
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

