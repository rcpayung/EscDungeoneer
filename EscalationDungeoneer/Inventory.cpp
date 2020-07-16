#include "Inventory.h"

Inventory::Inventory() : Menu() {
	this->items = std::vector<Item*>();

	sort_alpha = new Button(GameManager::SCREENWIDTH / 2, 210, 20, 20, "A");
	sort_alpha->setForeground(GameManager::GOLD);
	sort_alpha->setBackground(GameManager::DGRAY);
	sort_alpha->setHover(GameManager::GOLD, GameManager::DGRAY);
	sort_alpha->setStroke(2, GameManager::Gray20);
	sort_alpha->setAction(GameManager::pushCommand,"M:SORT:INBYAL"); // Menu: Sort: Inventory by alpha.
	sort_alpha->setTooltip("Sort items by their name.", 12, GameManager::GOLD, GameManager::DGRAY);

	sort_by_id = new Button(GameManager::SCREENWIDTH / 2 - 32, 210, 20, 20, "ID");
	sort_by_id->setForeground(GameManager::GOLD);
	sort_by_id->setBackground(GameManager::DGRAY);
	sort_by_id->setHover(GameManager::GOLD, GameManager::DGRAY);
	sort_by_id->setStroke(2, GameManager::Gray20);
	sort_by_id->setAction(GameManager::pushCommand,"M:SORT:INBYID"); // Menu: Sort: Inventory by ID.
	sort_by_id->setTooltip("Sort items by their ID.", 12, GameManager::GOLD, GameManager::DGRAY);

	close = new Button(GameManager::SCREENWIDTH - 330, 210, 20, 20, "X");
	close->setForeground(GameManager::GOLD);
	close->setBackground(GameManager::DGRAY);
	close->setHover(GameManager::GOLD, GameManager::DGRAY);
	close->setStroke(2, GameManager::Gray20);
	close->setAction(GameManager::pushCommand, "M:CLOS:INVENT"); // Menu: Sort: Inventory by alpha.
	close->setTooltip("Close the Inventory", 12, GameManager::GOLD, GameManager::DGRAY);

	help = new Button(GameManager::SCREENWIDTH - 360, 210, 20, 20, "?");
	help->setForeground(GameManager::GOLD);
	help->setBackground(GameManager::DGRAY);
	help->setHover(GameManager::GOLD, GameManager::DGRAY);
	help->setStroke(2, GameManager::Gray20);
	help->setAction(GameManager::pushCommand, "M:OPEN:INVHEL"); // Menu: Sort: Inventory by alpha.
	help->setTooltip("Help Me", 12, GameManager::GOLD, GameManager::DGRAY);


	L_inv = new Text("Inventory", 18, WBOLD, GameManager::GRAY, Vector2F(310,205), Vector2F(100,32));
	L_inv->setMiddle();
	L_equip = new Text("Equipment", 18, WBOLD, GameManager::GRAY, Vector2F(200,100), Vector2F(100, 30));
	L_coins = new Text("44,543,768",12,WNORMAL,GameManager::GOLD,Vector2F(200,200),Vector2F(100,30));
	L_level = new Text("GG", 15, WBOLD, GameManager::GREEN, Vector2F(100, 30), Vector2F(100, 30));

	back = { 300, 200, GameManager::SCREENWIDTH - 600,GameManager::SCREENHEIGHT - 400 };

	short int x = 315;
	short int y = 250;

	for (Uint8 i = 0; i < Uint8(MAX_ITEMS / 10); i++) {
		for (Uint8 j = 0; j < Uint8(MAX_ITEMS / 7); j++) {
			slots.push_back(new ItemSlot(x+j*48,y+i*48,32,32,GameManager::scale));
			x += 7;
		}
		y += 7;
		x = 315;
	}

	
}

void Inventory::sortinventory(std::string sort) {
	if (sort == "alpha") {

	}
	else if (sort == "ID") {
		for (Item* i : items) {
			for (Item* j : items) {
				if (i->getID() > j->getID()) {
					Item* temp = i;
					i = j;
					j = temp;
					delete temp;
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
	if (items.size() != MAX_ITEMS) {
		this->items.push_back(item);
		for (ItemSlot* lookforslot : slots) {
			if (lookforslot->getItem() == nullptr) {
				lookforslot->setItem(item);
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void Inventory::render() {
	SDL_SetRenderDrawColor(GameManager::rd, GameManager::DGRAY.r, GameManager::DGRAY.g, GameManager::DGRAY.b, GameManager::DGRAY.a);
	SDL_RenderFillRect(GameManager::rd, &back);

	for (ItemSlot* i : slots) {
		i->render();
	}

	close->render();
	help->render();
	sort_by_id->render();
	sort_alpha->render();
	L_inv->render();
	L_coins->render();
	L_equip->render();
	L_coins->render();
	L_level->render();



	__super::render();
}

void Inventory::update() {
	this->L_coins->setText(std::to_string(coins));
	for (ItemSlot* i : slots) {
		i->update();
	}

	close->update();
	help->update();
	sort_by_id->update();
	sort_alpha->update();

	__super::update();
}

void Inventory::clean() {

	for (ItemSlot* i : slots) {
		i->clean();
	}
	close->clean();
	help->clean();
	sort_by_id->clean();
	sort_alpha->clean();
	L_inv->clean();
	L_coins->clean();
	L_equip->clean();
	L_coins->clean();
	L_level->clean();


	__super::clean();
}

void Inventory::pollEvents(SDL_Event* e) {

	for (ItemSlot* i : slots) {
		i->handleEvents(e);
	}
	close->handleEvents(e);
	help->handleEvents(e);
	sort_by_id->handleEvents(e);
	sort_alpha->handleEvents(e);
	__super::pollEvents(e);
	switch (e->type) {
		case SDL_KEYDOWN:
		switch (e->key.keysym.sym) {
		case SDLK_ESCAPE:
			GameManager::pushCommand("M:CLOS:INVENT");
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