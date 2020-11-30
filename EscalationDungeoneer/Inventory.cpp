#include "Inventory.h"

Inventory::Inventory() : Menu() {
	numItems = 0;
	prompt = nullptr;
	coins = 0;
	selectedSlotID = -1;
	// Setup bounds.

	back = { 300, 200, GameManager::SCREENWIDTH - 600,GameManager::SCREENHEIGHT - 400 };
	borders.push_back(SDL_Rect{ back.x - 2,back.y - 2,back.w + 4,2 });
	borders.push_back(SDL_Rect{ back.x - 2,back.y,2,back.h + 2 });
	borders.push_back(SDL_Rect{ back.x - 2,back.y + back.h,back.w + 4,2 });
	borders.push_back(SDL_Rect{ back.x + back.w, back.y, 2, back.h + 2 });
	// Draw borders of inner tables
	borders.push_back(SDL_Rect{ back.x + 575, back.y, 2, back.h });
	borders.push_back(SDL_Rect{ back.x, back.y + 50, back.w,2 });
	borders.push_back(SDL_Rect{ back.x + 575, back.y + back.h - 70, back.w - 575, 2 });
	borders.push_back(SDL_Rect{ back.x + 575, back.y + back.h - 120, back.w - 575, 2 });
	borders.push_back(SDL_Rect{ back.x + 575, back.y + back.h - 184, back.w - 575, 2 });
	borders.push_back(SDL_Rect{ back.x + back.w - 205 + 23, back.y + 70, 2, 200}); // Equip Down - Center
	borders.push_back(SDL_Rect{ back.x + back.w - 150 + 23, back.y + 120, 2, 80 }); // Equip Down - Right
	borders.push_back(SDL_Rect{ back.x + back.w - 260 + 23, back.y + 120, 2, 80 }); // Equip Down - Left
	borders.push_back(SDL_Rect{ back.x + back.w - 250, back.y + 115 + 23, 150, 2 }); // Equip Across

	// Setup buttons.

	sort_alpha = new Button(GameManager::SCREENWIDTH / 2 + 10, 215, 20, 20, "A");
	sort_alpha->setForeground(GameManager::GOLD);
	sort_alpha->setBackground(GameManager::DGRAY);
	sort_alpha->setHover(GameManager::BLACK, GameManager::GRAY);
	sort_alpha->setStroke(2, GameManager::Gray20);
	sort_alpha->setAction(GameManager::pushCommand,"M:SORT:INBYAL"); // Menu: Sort: Inventory by alpha.
	sort_alpha->setTooltip("Sort items by name", 12, GameManager::GOLD, GameManager::DGRAY);

	sort_by_id = new Button(GameManager::SCREENWIDTH / 2 + 70, 215, 20, 20, "T");
	sort_by_id->setForeground(GameManager::GOLD);
	sort_by_id->setBackground(GameManager::DGRAY);
	sort_by_id->setHover(GameManager::BLACK, GameManager::GRAY);
	sort_by_id->setStroke(2, GameManager::Gray20);
	sort_by_id->setAction(GameManager::pushCommand,"M:SORT:INBYTY"); // Menu: Sort: Inventory by ID.
	sort_by_id->setTooltip("Sort items by type", 12, GameManager::GOLD, GameManager::DGRAY);

	sort_by_rarity = new Button(GameManager::SCREENWIDTH / 2 + 40, 215, 20, 20, "R");
	sort_by_rarity->setForeground(GameManager::GOLD);
	sort_by_rarity->setBackground(GameManager::DGRAY);
	sort_by_rarity->setHover(GameManager::BLACK, GameManager::GRAY);
	sort_by_rarity->setStroke(2, GameManager::Gray20);
	sort_by_rarity->setAction(GameManager::pushCommand, "M:SORT:INBYRR"); // Menu: Sort: Inventory by ID.
	sort_by_rarity->setTooltip("Sort items by rarity", 12, GameManager::GOLD, GameManager::DGRAY);

	close = new Button(back.x + back.w - 30, back.y + 15, 20, 20, "X");
	close->setForeground(GameManager::GOLD);
	close->setBackground(GameManager::DGRAY);
	close->setHover(GameManager::BLACK, GameManager::GRAY);
	close->setStroke(2, GameManager::Gray20);
	close->setAction(GameManager::pushCommand, "M:CLOS:INVENT"); // Menu: Sort: Inventory by alpha.
	close->setTooltip("Close the inventory", 12, GameManager::GOLD, GameManager::DGRAY);

	help = new Button(back.x + back.w - 60, back.y + 15, 20, 20, "?");
	help->setForeground(GameManager::GOLD);
	help->setBackground(GameManager::DGRAY);
	help->setHover(GameManager::BLACK, GameManager::GRAY);
	help->setStroke(2, GameManager::Gray20);
	help->setAction(GameManager::pushCommand, "M:OPEN:INVHEL"); // Menu: Sort: Inventory by alpha.
	help->setTooltip("Help Me", 12, GameManager::GOLD, GameManager::DGRAY);

	// Setup labels.

	L_inv = new Text("Inventory", 18, WBOLD, GameManager::LGRAY, Vector2F(back.x + 15, 200), Vector2F(100, 50));
	L_inv->setMiddle();
	L_equip = new Text("Equipment", 18, WBOLD, GameManager::LGRAY, Vector2F(back.x + (back.w / 2) + 120, 200), Vector2F(100, 50));
	L_equip->setMiddle();
	L_level = new Text("Level 54", 18, WBOLD, GameManager::LGRAY, Vector2F(back.x + 575, back.y + back.h - 120), Vector2F(365, 50));
	L_level->setCenter();
	L_level->setMiddle();

	// Setup glyph slots:
	
	I_glyph_tri = new GlyphSlot((back.x + back.w) - 265, back.y+back.h - 175, 48, 48);
	I_glyph_tri->setGlyphType(GlyphType::TRIANGLE);
	I_glyph_tri->setBackground("assets/triangleGlyphbg.bmp",0,0);
	I_glyph_sqr = new GlyphSlot((back.x + back.w) - 205, back.y + back.h - 175, 48, 48);
	I_glyph_sqr->setGlyphType(GlyphType::SQUARE);
	I_glyph_sqr->setBackground("assets/sqrGlyphbg.bmp",0,0);
	I_glyph_PENT = new GlyphSlot((back.x + back.w) - 145, back.y + back.h - 175, 48, 48);
	I_glyph_PENT->setGlyphType(GlyphType::PENTAGRAM);
	I_glyph_PENT->setBackground("assets/octoGlyphbg.bmp",0,0);

	// Setup armor slots:

	head = new ArmorSlot(back.x + back.w - 205, back.y + 60, 48, 48);
	head->setBackground("assets/inventoryslots.bmp",0,0);
	head->setArmorType(ArmorType::HELMET);
	torso = new ArmorSlot(back.x + back.w - 205, back.y + 115, 48, 48);
	torso->setBackground("assets/inventoryslots.bmp",1,0);
	torso->setArmorType(ArmorType::BODY);
	legs = new ArmorSlot(back.x + back.w - 205, back.y + 170, 48, 48);
	legs->setBackground("assets/inventoryslots.bmp", 2, 0);
	legs->setArmorType(ArmorType::LEGS);
	feet = new ArmorSlot(back.x + back.w - 205, back.y + 225, 48, 48);
	feet->setBackground("assets/inventoryslots.bmp", 3, 0);
	feet->setArmorType(ArmorType::BOOTS);
	righthand = new WeaponSlot(back.x + back.w - 150, back.y + 115, 48, 48);
	righthand->setBackground("assets/inventoryslots.bmp", 4, 0);
	righthand->setWeaponType(WeaponType::UNSET);
	lefthand = new ArmorSlot(back.x + back.w - 260, back.y + 115, 48, 48);
	lefthand->setBackground("assets/inventoryslots.bmp", 5, 0);
	lefthand->setArmorType(ArmorType::SHIELD);
	leftring = new ArmorSlot(back.x + back.w - 260, back.y + 170, 48, 48);
	leftring->setBackground("assets/inventoryslots.bmp", 6, 0);
	leftring->setArmorType(ArmorType::RING);
	rightring = new ArmorSlot(back.x + back.w - 150, back.y + 170, 48, 48);
	rightring->setBackground("assets/inventoryslots.bmp", 6, 0);
	rightring->setArmorType(ArmorType::RING);


	short int x = back.x + 15;
	short int y = back.y + 69;

	for (Uint8 i = 0; i < Uint8(MAX_ITEMS / 10); i++) {
		for (Uint8 j = 0; j < Uint8(MAX_ITEMS / 7); j++) {
			slots.push_back(new ItemSlot(x + j * 48, y + i * 48, 48, 48, GameManager::scale));
			x += 7;
		}
		y += 7;
		x = back.x + 15;
	}
	S_coins = new Sprite("inventory_coins","assets/coins.png", Vector2F(back.x + 600, back.y+back.h-50), Vector2F{ 32,32 }, 1.0f);
	L_coins = new Text("44,543,768", 15, WNORMAL, GameManager::GOLD, Vector2F(back.x + 640, back.y + back.h - 50), Vector2F(120, 32));
	L_coins->setMiddle();

	this->itemCount = new Text(std::to_string(this->numItems) + "/" + std::to_string(this->MAX_ITEMS), 11, WBOLD, GameManager::GRAY, Vector2F(back.x + 400, back.y + 15), Vector2F(50, 20));

	selectedSlot = nullptr;

	addComponent(close);
	addComponent(help);
	addComponent(L_inv);
	addComponent(L_coins);
	addComponent(L_equip);
	addComponent(L_coins);
	addComponent(L_level);
}

void Inventory::render() {
	SDL_SetRenderDrawColor(GameManager::rd, GameManager::DGRAY.r, GameManager::DGRAY.g, GameManager::DGRAY.b, 200);
	SDL_RenderFillRect(GameManager::rd, &back);
	GameManager::setDrawColor(GameManager::Gray20);
	for (SDL_Rect i : borders) {
		SDL_RenderFillRect(GameManager::rd, &i);
	}

	S_coins->render();

	__super::render();

	I_glyph_PENT->render();
	I_glyph_sqr->render();
	I_glyph_tri->render();
	feet->render();
	rightring->render();
	legs->render();
	leftring->render();
	righthand->render();
	torso->render(); 
	lefthand->render();
	head->render();
	/*

	*/
	itemCount->render();
	for (int i = static_cast<int>(slots.size() - 1); i >= 0; i--) {
		if (slots.at(i) != selectedSlot) {
			slots.at(i)->render();
			slots.at(i)->renderItem();
		}
	}


	sort_by_id->render();
	sort_by_rarity->render();
	sort_alpha->render();
	if (prompt != nullptr) {
		prompt->render();
	}
	if (selectedSlot != nullptr) {
		selectedSlot->render();
		selectedSlot->renderItem();
	}
}

void Inventory::update() {
	this->L_coins->setText(std::to_string(coins));
	this->L_coins->setMiddle();

	I_glyph_tri->update();
	I_glyph_PENT->update();
	I_glyph_sqr->update();
	head->update();
	torso->update();
	legs->update();
	feet->update();
	lefthand->update();
	righthand->update();
	leftring->update();
	rightring->update();

	this->itemCount->setText(std::to_string(this->numItems) + "/" + std::to_string(this->MAX_ITEMS));
	this->itemCount->setMiddle();
	this->itemCount->setCenter();

	for (ItemSlot* i : slots) {
		i->update();
		if (i->getItem() != nullptr && i == selectedSlot) {
			i->getItem()->setPosition(GameManager::mx, GameManager::my);
		}
		else {
			if (i->getItem() != nullptr) {
				i->getItem()->setPosition(i->getPosition().X, i->getPosition().Y);
			}
		}
	}
	if (selectedSlot != nullptr && selectedSlot->getItem() != nullptr) {
		selectedSlot->getItem()->setPosition(GameManager::mx, GameManager::my);
	}

	__super::update();
	sort_by_id->update();
	sort_by_rarity->update();
	sort_alpha->update();
	if (prompt != nullptr) {
		prompt->update();
	}
}

void Inventory::clean() {
	S_coins->clean();
	for (ItemSlot* i : slots) {
		i->clean();
	}
	I_glyph_tri->clean();
	I_glyph_PENT->clean();
	I_glyph_sqr->clean();

	head->clean();
	torso->clean();
	legs->clean();
	feet->clean();
	lefthand->clean();
	righthand->clean();
	leftring->clean();
	rightring->clean();
	this->itemCount->clean();

	if (prompt != nullptr) {
		prompt->clean();
	}
	__super::clean();
}


void Inventory::sortinventory(std::string sort) {
	Item* temp;
	if (sort == "ALPHA") {
		for (ItemSlot* i : slots) {
			if (i->getItem() == nullptr) continue;
			for (ItemSlot* j : slots) {
				if (j->getItem() == nullptr) continue;
				if (j->getItem()->getName().at(0) > i->getItem()->getName().at(0) && j->getItem()->getName().at(0) != i->getItem()->getName().at(0)) {
					temp = j->getItem();
					j->setItem(i->getItem());
					i->setItem(temp);
					i->update();
					j->update();
				}
			}
		}
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
			if (i->getItem()->getID() > j->getItem()->getID()) {
				temp = i->getItem();
				i->setItem(j->getItem());
				j->setItem(temp);
				i->update();
				j->update();
			}
		}
	}
	}
	// Make sure that items are right next to each other in the inventory:
	std::vector<Item*> items;
	for (ItemSlot* i : slots) {
		if (i->getItem() != nullptr)
			items.push_back(i->getItem());
		i->setItem(nullptr);
	}
	for (int i = 0; i < slots.size(); i++) {
		if (i < items.size())
			slots.at(i)->setItem(items.at(i));
		else
			break;
	}
	items.clear();

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

bool Inventory::removeItemAt(int index) {
	if (index > 70) {
		switch (index) {
		case 71:
			I_glyph_PENT->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 72:
			I_glyph_sqr->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 73:
			I_glyph_tri->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 74:
			lefthand->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 75:
			righthand->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 76:
			head->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 77:
			torso->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 78:
			legs ->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 79:
			feet->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 80:
			rightring->setItem(nullptr);
			numItems--;
			return true;
			break;
		case 81:
			leftring->setItem(nullptr);
			numItems--;
			return true;
			break;
		default:
			break;
		}
	}
	else if (this->slots.at(index)->getItem() != nullptr) {
		this->slots.at(index)->setItem(nullptr);
		numItems--;
		return true;
	}
	return false;
}

bool Inventory::closePrompt() {
	if (this->prompt != nullptr) {
		this->prompt = nullptr;
		return true;
	}
	else
		return false;

}

ItemSlot* Inventory::findEmptySlot() {
	for (ItemSlot* i : slots) {
		if (i->getItem() == nullptr) {
			return i;
		}
	}
	return nullptr;
}

bool Inventory::unequipShield() {
	if (lefthand->getItem() != nullptr) {
		ItemSlot* slot = findEmptySlot();
		if (slot != nullptr) {
			slot->setItem(lefthand->getItem());
			lefthand->setItem(nullptr);
			numItems++;
			return true;
		}
		else {
			printf("INV::unequipShield(): Error with nullptr slots or slot not available to move item.");
			return false;
		}
	}
	else {
		printf("INV::unequpShield(): Either has error or item in slot is not set.\n");
		return false;
	}
}


bool Inventory::checkItem(ItemSlot* a) {
	bool result = false;
	// Check the allowed item type:
	switch (a->getAllowedItemType()) {
	case ItemType::UNSET:
		result = true;
		break;
	case ItemType::ARMOR:
		if (selectedSlot->getItem()->getType() == ItemType::ARMOR) {
			switch (((ArmorSlot*)a)->getAType()) {
			case ArmorType::AMULET:
				(selectedSlot->getItem())->getAType() == ArmorType::AMULET ? (result = true) : (result = false);
				break;
			case ArmorType::HELMET:
				(selectedSlot->getItem())->getAType() == ArmorType::HELMET ? (result = true) : (result = false);
				break;
			case ArmorType::BODY:
				(selectedSlot->getItem())->getAType() == ArmorType::BODY ? (result = true) : (result = false);
				break;
			case ArmorType::LEGS:
				(selectedSlot->getItem())->getAType() == ArmorType::LEGS ? (result = true) : (result = false);
				break;
			case ArmorType::BOOTS:
				(selectedSlot->getItem())->getAType() == ArmorType::BOOTS ? (result = true) : (result = false);
				break;
			case ArmorType::SHIELD:
				// If the item inside the weapon slot is a gun or a bow, we dont want to allow the shield to be placed in the slot.
				if (righthand->getItem() != nullptr && (righthand->getItem()->getWType() == WeaponType::GUN || righthand->getItem()->getWType() == WeaponType::BOW)) {
					prompt = new Prompt(GameManager::SCREENWIDTH / 2 - 200, GameManager::SCREENHEIGHT / 2 - 100, 400, 250,"You can't wear a shield with a gun or bow.");
					prompt->setConfirm(GameManager::pushCommand, "M:CLOS:INVPMT");
					if (unequipShield()) {
						result = true;
					}
					else {
						result = false;
					}
					break;
				}
				(selectedSlot->getItem())->getAType() == ArmorType::SHIELD ? (result = true) : (result = false);
				break;
			case ArmorType::GLOVES:
				(selectedSlot->getItem())->getAType() == ArmorType::GLOVES ? (result = true) : (result = false);
				break;
			case ArmorType::RING:
				(selectedSlot->getItem())->getAType() == ArmorType::RING ? (result = true) : (result = false);
				break;
			case ArmorType::UNSET:
				result = true;
				break;
			default:
				break;
			}
		}
		break;
	case ItemType::CONSUMABLE:
		if (selectedSlot->getItem()->getType() == ItemType::CONSUMABLE) {
			break;
		}
		break;
		// If the item type is a glyph:
	case ItemType::GLYPH:
		// Check that the item is a glyph:
		if (selectedSlot->getItem()->getType() == ItemType::GLYPH) {
			// If the item is in fact a glyph, check what type of glyph that the glyphslot can hold:
			switch (((GlyphSlot*)a)->getGType()) {
				// If its unset, can hold any:
			case GlyphType::UNSET:
				result = true;
				break;
			case GlyphType::PENTAGRAM:
				(selectedSlot->getItem())->getGType() == GlyphType::PENTAGRAM ? (result = true) : (result = false);
				break;
			case GlyphType::TRIANGLE:
				(selectedSlot->getItem())->getGType() == GlyphType::TRIANGLE ? (result = true) : (result = false);
				break;
			case GlyphType::SQUARE:
				(selectedSlot->getItem())->getGType() == GlyphType::SQUARE ? (result = true) : (result = false);
				break;
			default:
				break;
			}
			break;
		}
		break;
	case ItemType::WEAPON:
		if (selectedSlot->getItem()->getType() == ItemType::WEAPON) {
			if (lefthand->getItem() != nullptr && (selectedSlot->getItem()->getWType() == WeaponType::GUN || selectedSlot->getItem()->getWType() == WeaponType::BOW)) {
				prompt = new Prompt(GameManager::SCREENWIDTH / 2 - 200, GameManager::SCREENHEIGHT / 2 - 100, 400, 250, "You can't wear a shield with a gun or bow.");
				prompt->setConfirm(GameManager::pushCommand, "M:CLOS:INVPMT");
				if (unequipShield())
					result = true;
				else
					result = false;
				break;
			}
			result = true;
		}
		break;
	case ItemType::MISC:
		break;
	default:
		break;

	}
	// Armor slots, basically moving the other direction.
	if (a->getItem() != nullptr) {
		if (selectedSlotID > MAX_ITEMS) {
			// if were moving from the armor slots to the inventory (Removing armors or glyphs, etc.)
			if (selectedSlot->getItem()->getType() == a->getItem()->getType()) {
				switch (a->getItem()->getType()) {
				case ItemType::ARMOR:
					selectedSlot->getItem()->getAType() == a->getItem()->getAType() ? result = true : result = false;
					break;
				case ItemType::CONSUMABLE:
					result = true;
					break;
				case ItemType::GLYPH:
					selectedSlot->getItem()->getGType() == a->getItem()->getGType() ? result = true : result = false;
					break;
				case ItemType::WEAPON:
					result = true;
					break;
				default:
					break;

				}
			}
			else {
				result = false;
			}
		}
	}

	return result;
}
/*
bool swapItems(ItemSlot* a, ItemSlot* b) {
	Item temp;
	if (a->getItem() != nullptr) {
		if (checkItem(a)) {
			temp = *a->getItem();
			a->setItem(b->getItem());
			b->setItem(&temp);

		}
	}
}
*/

void Inventory::swapItems(ItemSlot* a) {
	Item* temp;
	if (a->getItem() != nullptr) {
		// check the item type:
		if (checkItem(a)) {
			temp = a->getItem();
			a->setItem(selectedSlot->getItem());
			a->getItem()->setPosition(a->getPosition().X, a->getPosition().Y);
			selectedSlot->setItem(temp);
			selectedSlot->getItem()->setPosition(selectedSlot->getPosition().X, selectedSlot->getPosition().Y);
			selectedSlot = nullptr;
			selectedSlotID = -1;
		}
		else {
			selectedSlot->getItem()->setPosition(selectedSlot->getPosition().X, selectedSlot->getPosition().Y);
			selectedSlot = nullptr;
			selectedSlotID = -1;
		}
		
	}
	else {
		if (checkItem(a)) {
			if (a->getItem() == nullptr && selectedSlotID < 71) {
				numItems--;
			}
			else {
				numItems++;
			}
			a->setItem(selectedSlot->getItem());
			a->getItem()->setPosition(a->getPosition().X, a->getPosition().Y);
			selectedSlot->setItem(nullptr);
			selectedSlot = nullptr;
			selectedSlotID = -1;
			
		}
		else {
			selectedSlot->getItem()->setPosition(selectedSlot->getPosition().X, selectedSlot->getPosition().Y);
			selectedSlot = nullptr;
			selectedSlotID = -1;
		}
	}
}

bool checkBounds(ItemSlot* slot) {
	if (slot->getPosition().X < GameManager::mx && (slot->getSize().X + slot->getPosition().X) > GameManager::mx
		&& slot->getPosition().Y < GameManager::my && (slot->getSize().Y + slot->getPosition().Y) > GameManager::my) {
		return true;
	}
	else {
		return false;
	}
}

void Inventory::pollEvents(SDL_Event* e) {
	sort_by_id->handleEvents(e);
	sort_by_rarity->handleEvents(e);
	sort_alpha->handleEvents(e);
	if (prompt == nullptr) {
		for (ItemSlot* i : slots) {
			i->handleEvents(e);
		}
	}
	I_glyph_tri->handleEvents(e);
	I_glyph_PENT->handleEvents(e);
	I_glyph_sqr->handleEvents(e);

	legs->handleEvents(e);
	feet->handleEvents(e);
	head->handleEvents(e);
	torso->handleEvents(e);

	lefthand->handleEvents(e);
	righthand->handleEvents(e);
	leftring->handleEvents(e);
	rightring->handleEvents(e);

	__super::pollEvents(e);
	if (prompt != nullptr) {
		prompt->handleEvents(e);
	}
	switch (e->type) {
	case SDL_MOUSEMOTION:
		// ItemInformation (If hovering over an item, show the item information).
		for (int i = 0; i < slots.size(); i++) {
			if (checkBounds(slots.at(i))) {
				if (slots.at(i)->getItem() != nullptr) {
					// Show the slot item stats.
					break;
				}
				else {
					this->showDetails = false;
				}
				break;
			}
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (e->button.button) {
		case SDL_BUTTON_LEFT:
			if (this->prompt == nullptr) {
				if (!GameManager::leftLock) {
					for (int i = 0; i < slots.size(); i++) {
						if (checkBounds(slots.at(i))) {
							if (slots.at(i)->getItem() != nullptr) {
								this->selectedSlot = slots.at(i);
								selectedSlotID = i;
								GameManager::leftLock = true;
								break;
							}
						}
					}
					if (checkBounds(I_glyph_PENT) && I_glyph_PENT->getItem() != nullptr) {
						this->selectedSlot = I_glyph_PENT;
						selectedSlotID = 71;
						GameManager::leftLock = true;
						break;
					}
					else if (checkBounds(I_glyph_sqr) && I_glyph_sqr->getItem() != nullptr) {
						this->selectedSlot = I_glyph_sqr;
						selectedSlotID = 72;
						GameManager::leftLock = true;
						break;
					}
					else if (checkBounds(I_glyph_tri) && I_glyph_tri->getItem() != nullptr) {
						this->selectedSlot = I_glyph_tri;
						selectedSlotID = 73;
						GameManager::leftLock = true;
						break;
					}
					// ARMOR AND WEAPON SLOTS:
					if (checkBounds(lefthand) && lefthand->getItem() != nullptr) {
						this->selectedSlot = lefthand;
						selectedSlotID = 74;
						GameManager::leftLock = true;
						break;
					}
					if (checkBounds(righthand) && righthand->getItem() != nullptr) {
						this->selectedSlot = righthand;
						selectedSlotID = 75;
						GameManager::leftLock = true;
						break;
					}
					if (checkBounds(head) && head->getItem() != nullptr) {
						this->selectedSlot = head;
						selectedSlotID = 76;
						GameManager::leftLock = true;
						break;
					}
					if (checkBounds(torso) && torso->getItem() != nullptr) {
						this->selectedSlot = torso;
						selectedSlotID = 77;
						GameManager::leftLock = true;
						break;
					}
					if (checkBounds(legs) && legs->getItem() != nullptr) {
						this->selectedSlot = legs;
						selectedSlotID = 78;
						GameManager::leftLock = true;
						break;
					}
					if (checkBounds(feet) && feet->getItem() != nullptr) {
						this->selectedSlot = feet;
						selectedSlotID = 79;
						GameManager::leftLock = true;
						break;
					}
					if (checkBounds(rightring) && rightring->getItem() != nullptr) {
						this->selectedSlot = rightring;
						selectedSlotID = 80;
						GameManager::leftLock = true;
						break;
					}
					if (checkBounds(leftring) && leftring->getItem() != nullptr) {
						this->selectedSlot = leftring;
						selectedSlotID = 81;
						GameManager::leftLock = true;
						break;
					}
				}
			}
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (e->button.button) {
		case SDL_BUTTON_LEFT:
			if (GameManager::leftLock) {
				for (int i = 0; i < slots.size(); i++) {
					if (checkBounds(slots.at(i))) {
						swapItems(slots.at(i));
						GameManager::leftLock = false;
						break;
					}
				}
				if (selectedSlot != nullptr) {
					if (checkBounds(I_glyph_PENT)) {
						swapItems(I_glyph_PENT);
						GameManager::leftLock = false;
						break;
					}
					if (checkBounds(I_glyph_tri)) {
						swapItems(I_glyph_tri);
						GameManager::leftLock = false;
						break;
					}
					if (checkBounds(I_glyph_sqr)) {
						swapItems(I_glyph_sqr);
						GameManager::leftLock = false;
						break;
					}
					// ARMOR AND WEAPON SLOTS:
					if (checkBounds(lefthand)) {
						swapItems(lefthand);
						GameManager::leftLock = false;
						break;
					}
					if (checkBounds(righthand)) {
						swapItems(righthand);
						GameManager::leftLock = false;
						break;
					}
					if (checkBounds(head)) {
						swapItems(head);
						GameManager::leftLock = false;
						break;
					}
					if (checkBounds(torso)) {
						swapItems(torso);
						GameManager::leftLock = false;
						break;
					}
					if (checkBounds(legs)) {
						swapItems(legs);
						GameManager::leftLock = false;
						break;
					}
					if (checkBounds(feet)) {
						swapItems(feet);
						GameManager::leftLock = false;
						break;
					}
					if (checkBounds(rightring)) {
						swapItems(rightring);
						GameManager::leftLock = false;
						break;
					}
					if (checkBounds(leftring)) {
						swapItems(leftring);
						GameManager::leftLock = false;
						break;
					}
					//Check here for item dropping and itemslot dropping to other slots than the inventory.
					if (GameManager::mx > back.x&& GameManager::mx < (back.x + back.w) && GameManager::my > back.y&& GameManager::my < (back.y + back.h)) {
						selectedSlot->getItem()->setPosition(selectedSlot->getPosition().X, selectedSlot->getPosition().Y);
						selectedSlot = nullptr;
						selectedSlotID = -1;

						GameManager::leftLock = false;
						break;
					}
					prompt = new Prompt(GameManager::SCREENWIDTH / 2 - 200, GameManager::SCREENHEIGHT / 2 - 100, 400, 250, "Are you sure you want to delete: " + selectedSlot->getItem()->getRarityString() + " " + selectedSlot->getItem()->getName() +"?");
					prompt->setConfirm(GameManager::pushCommand, "I:delI:" + std::to_string(selectedSlotID));
					prompt->setCancel(GameManager::pushCommand,"M:CLOS:INVPMT");
					// There was something that went wrong (Item was dropped outside of inventory slots.
					selectedSlot->getItem()->setPosition(selectedSlot->getPosition().X, selectedSlot->getPosition().Y);
					selectedSlot = nullptr;
					selectedSlotID = -1;
				}
				GameManager::leftLock = false;
			}
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e->key.keysym.sym) {
		case SDLK_RETURN:
			if (prompt != nullptr) {
				prompt->runConfirm();
			}
			break;
		case SDLK_ESCAPE:
			if (prompt == nullptr) {
				GameManager::pushCommand("M:CLOS:INVENT");
			}
			else {
				closePrompt();
			}
			break;
		case SDLK_BACKSLASH:
			if (GameManager::devMode) this->coins += 777;
			break;
		case SDLK_i:
			if (GameManager::devMode) GameManager::pushCommand("G:GIVE:1");
			break;
		case SDLK_u:
			if (GameManager::devMode) GameManager::pushCommand("G:GIVE:2");
			break;
		case SDLK_y:
			if (GameManager::devMode) GameManager::pushCommand("G:GIVE:3");
			break;
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