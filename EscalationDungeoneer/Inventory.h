#pragma once
#include "GameManager.h"
#include "Menu.h"
#include "Armor.h"
#include "Weapon.h"
#include "Glyph.h"
#include "ItemSlot.h"
#include "Prompt.h"
#include "ItemDetails.h"


class Inventory : public Menu {
private:
	std::vector<ItemSlot*> slots;
	std::vector<ItemSlot*> armorslots;
	bool showDetails = false;
	const int MAX_ITEMS = 70;
	int numItems;
	long coins;
	ItemSlot* selectedSlot;
	int selectedSlotID;

	// EQUIPMENT
	Armor* head, * neck, * cape, * torso, * legs, * feet, * lefthand;
	Armor* leftring, * rightring;
	Weapon* righthand;
	Item* item;
	ItemDetails* details;
	
	// GLYPHS
	Glyph* triangle, * square, * diamond;
	ItemSlot* I_glyph_tri, * I_glyph_sqr, * I_glyph_PENT;
	Button* sort_alpha, * sort_by_id, * sort_by_rarity, * close, * help;
	Sprite* S_coins, * S_glyphPENT_bg, * S_glyphTRI_bg, * S_glyphSQR_bg, * S_equipback, * S_invback;
	SDL_Rect back;
	Prompt* prompt;
protected:
	
public:
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

