#include "Inventory.h"

Inventory::Inventory() : Menu() {
	
	back = { 300, 200, GameManager::SCREENWIDTH - 600,GameManager::SCREENHEIGHT - 400 };


	sort_alpha = new Button(GameManager::SCREENWIDTH / 2 + 10, 215, 20, 20, "A");
	sort_alpha->setForeground(GameManager::GOLD);
	sort_alpha->setBackground(GameManager::DGRAY);
	sort_alpha->setHover(GameManager::GOLD, GameManager::DGRAY);
	sort_alpha->setStroke(2, GameManager::Gray20);
	sort_alpha->setAction(GameManager::pushCommand,"M:SORT:INBYAL"); // Menu: Sort: Inventory by alpha.
	sort_alpha->setTooltip("Sort items by their name.", 12, GameManager::GOLD, GameManager::DGRAY);

	sort_by_id = new Button(GameManager::SCREENWIDTH / 2 + 70, 215, 20, 20, "ID");
	sort_by_id->setForeground(GameManager::GOLD);
	sort_by_id->setBackground(GameManager::DGRAY);
	sort_by_id->setHover(GameManager::GOLD, GameManager::DGRAY);
	sort_by_id->setStroke(2, GameManager::Gray20);
	sort_by_id->setAction(GameManager::pushCommand,"M:SORT:INBYID"); // Menu: Sort: Inventory by ID.
	sort_by_id->setTooltip("Sort items by their ID.", 12, GameManager::GOLD, GameManager::DGRAY);

	sort_by_rarity = new Button(GameManager::SCREENWIDTH / 2 + 40, 215, 20, 20, "R");
	sort_by_rarity->setForeground(GameManager::GOLD);
	sort_by_rarity->setBackground(GameManager::DGRAY);
	sort_by_rarity->setHover(GameManager::GOLD, GameManager::DGRAY);
	sort_by_rarity->setStroke(2, GameManager::Gray20);
	sort_by_rarity->setAction(GameManager::pushCommand, "M:SORT:INBYRR"); // Menu: Sort: Inventory by ID.
	sort_by_rarity->setTooltip("Sort items by their Rarity", 12, GameManager::GOLD, GameManager::DGRAY);

	close = new Button(back.x + back.w - 30, back.y + 10, 20, 20, "X");
	close->setForeground(GameManager::GOLD);
	close->setBackground(GameManager::DGRAY);
	close->setHover(GameManager::GOLD, GameManager::DGRAY);
	close->setStroke(2, GameManager::Gray20);
	close->setAction(GameManager::pushCommand, "M:CLOS:INVENT"); // Menu: Sort: Inventory by alpha.
	close->setTooltip("Close the Inventory", 12, GameManager::GOLD, GameManager::DGRAY);

	help = new Button(back.x + back.w - 60, back.y + 10, 20, 20, "?");
	help->setForeground(GameManager::GOLD);
	help->setBackground(GameManager::DGRAY);
	help->setHover(GameManager::GOLD, GameManager::DGRAY);
	help->setStroke(2, GameManager::Gray20);
	help->setAction(GameManager::pushCommand, "M:OPEN:INVHEL"); // Menu: Sort: Inventory by alpha.
	help->setTooltip("Help Me", 12, GameManager::GOLD, GameManager::DGRAY);


	L_inv = new Text("Inventory", 18, WBOLD, GameManager::GRAY, Vector2F(back.x + 15, 200), Vector2F(100, 50));
	L_inv->setMiddle();
	L_equip = new Text("Equipment", 18, WBOLD, GameManager::GRAY, Vector2F(back.x + (back.w / 2) + 120, 200), Vector2F(100, 50));
	L_equip->setMiddle();
	L_coins = new Text("44,543,768", 15, WNORMAL, GameManager::GOLD, Vector2F(back.x + 640, back.y + back.h - 70-16), Vector2F(120, 32));
	L_coins->setMiddle();
	L_level = new Text("Level 54 Warlock", 15, WBOLD, GameManager::LGRAY, Vector2F(back.x + 570, back.y + 300), Vector2F(350, 50));
	L_level->setCenter();
	L_level->setMiddle();

	I_glyph_tri = new ItemSlot(0, 0, 48, 48, 1.0f);
	S_glyphTRI_bg = new Sprite("assets/TriangleGlyphbg.bmp", Vector2F(0,0), Sizer{50,50},1.0f);
	S_coins = new Sprite("assets/coins.png", Vector2F(back.x + 600, back.y + back.h - 70 - 16), Sizer{ 32,32 }, 1.0f);

	short int x = back.x + 15;
	short int y = back.y + 50;

	for (Uint8 i = 0; i < Uint8(MAX_ITEMS / 10); i++) {
		for (Uint8 j = 0; j < Uint8(MAX_ITEMS / 7); j++) {
			slots.push_back(new ItemSlot(x + j * 48, y + i * 48, 48, 48, GameManager::scale));
			x += 7;
		}
		y += 7;
		x = back.x + 15;
	}

	slots.at(0)->setItem(item);

	addComponent(close);
	addComponent(help);
	addComponent(sort_by_id);
	addComponent(sort_by_rarity);
	addComponent(sort_alpha);
	addComponent(L_inv);
	addComponent(L_coins);
	addComponent(L_equip);
	addComponent(L_coins);
	addComponent(L_level);
}

void Inventory::sortinventory(std::string sort) {
	Item* temp;
	if (sort == "ALPHA") {

	}
	else if (sort == "RARITY") {
		for (ItemSlot* i : slots) {
			if (i->getItem() == nullptr) continue;
			for (ItemSlot* j : slots) {
				if (j->getItem() == nullptr) continue;
				if (j->getItem()->getRarity() < i->getItem()->getRarity()) {
					temp = j->getItem();
					j->setItem(i->getItem());
					i->setItem(temp);
					i->update();
					j->update();
				}
			}
		}
	}
	else if (sort == "ID") {
		for (ItemSlot* i : slots) {
			if (i->getItem() == nullptr) continue;
			for (ItemSlot* j : slots) {
				if (j->getItem() == nullptr) continue;
				if (i->getItem()->getGID() > j->getItem()->getGID()) {
					temp = i->getItem();
					i->setItem(j->getItem());
					j->setItem(temp);
					i->update();
					j->update();
				}
			}
		}
	}
}

bool Inventory::loadGameInventory(const char* location) {
	return false;
}
/*
bool Inventory::saveGameInventory(const char* location) {
	return false;
}
*/
bool Inventory::pushItem(Item* item) {
	if (numItems < MAX_ITEMS) {
		for (ItemSlot* lookforslot : slots) {
			if (lookforslot->getItem() == nullptr) {
				lookforslot->setItem(item);
				break;
			}
			else {
				if (lookforslot->getItem()->getID() == item->getID() && lookforslot->getItem()->is_stackable()) {
					lookforslot->getItem()->increase_stack(item->getStack());
					break;
				}
			}
		}
		numItems++;
		return true;
	}
	else {
		printf("Player inventory is full.\n");
		return false;
	}
}
/*
bool Inventory::removeItem(Item* item) {

}
*/

void Inventory::render() {
	SDL_SetRenderDrawColor(GameManager::rd, GameManager::DGRAY.r, GameManager::DGRAY.g, GameManager::DGRAY.b, GameManager::DGRAY.a);
	SDL_RenderFillRect(GameManager::rd, &back);
	S_coins->render(0.0f);
	S_glyphTRI_bg->render(0.0f);

	__super::render();

	for (int i = static_cast<int>(slots.size() - 1); i >= 0; i--) {
		slots.at(i)->render();
	}
	I_glyph_tri->render();
	S_glyphTRI_bg->render(0.0f);
}

void Inventory::update() {
	this->L_coins->setText(std::to_string(coins));
	this->L_coins->setMiddle();
	for (ItemSlot* i : slots) {
		i->update();
	}
	I_glyph_tri->update();
	__super::update();
}

void Inventory::clean() {
	S_coins->clean();
	for (ItemSlot* i : slots) {
		i->clean();
	}
	I_glyph_tri->clean();
	S_glyphTRI_bg->clean();

	__super::clean();
}

void Inventory::pollEvents(SDL_Event* e) {
	for (ItemSlot* i : slots) {
		i->handleEvents(e);
	}
	I_glyph_tri->handleEvents(e);
	__super::pollEvents(e);
	switch (e->type) {
		case SDL_KEYDOWN:
		switch (e->key.keysym.sym) {
		case SDLK_ESCAPE:
			GameManager::pushCommand("M:CLOS:INVENT");
			break;
		case SDLK_BACKSLASH:
			if (GameManager::devMode) this->coins += 777;
			break;
		case SDLK_i:
			if (GameManager::devMode) GameManager::pushCommand("G:GIVE:000001");
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Inventory::addCoins(long amount) {
	this->coins += amount;
}

void Inventory::removeCoins(long amount) {
	this->coins -= amount;
}