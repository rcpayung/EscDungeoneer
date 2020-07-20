#include "ItemDetails.h"

ItemDetails::ItemDetails(int x, int y, int w, int h) : UIComponent(x,y,w,h,GameManager::scale) {
	lasty = y;
	name = new Text("ItemName", 14, WBOLD, GameManager::BLACK, Vector2F(x, lasty), Vector2F(w, 20));
	drag = new Text("This item is equippable. Drag to respective slot.", 12, WNORMAL, GameManager::GRAY,Vector2F(x,y+h-20), Vector2F(w,20));
	item = nullptr;
	dest = { x,y,w,h };
	border = { x - 2,y - 2,w + 4,h + 4 };

	lasty = y + 20;
}

void ItemDetails::update() {
	lasty = dest.y;
	int lastyoriginal = lasty;
	this->setPosition(GameManager::mx+25, GameManager::my+25);
	border = {dest.x - 2,dest.y - 2,dest.w + 4,dest.h + 4 };
	for (Text* i : stats) {
		i->setBounds(dest.x, lastyoriginal, dest.w, 30);
		lastyoriginal += 30;
	}
}

void ItemDetails::render() {
	GameManager::setDrawColor(GameManager::Gray20);
	SDL_RenderFillRect(GameManager::rd, &border);
	GameManager::setDrawColor(GameManager::DGRAY);
	SDL_RenderFillRect(GameManager::rd, &dest);

	if (item != nullptr)
		for (Text* i : stats) {
			i->render();
		}

	name->render();
	drag->render();
}

void ItemDetails::clean() {
	name->clean();
	drag->clean();
}

void ItemDetails::setItem(Item* item) {
	this->item = item;
	int lastyoriginal = lasty;
	if (item != nullptr) {
		this->stats.push_back(new Text("Attack Bonus: +" + std::to_string(item->getstats().ATT), 12, WBOLD, GameManager::LGRAY, Vector2F(dest.x, lastyoriginal), Vector2F(dest.w, 30)));
		lastyoriginal += 30;
		this->stats.push_back(new Text("Defense Bonus: +" + std::to_string(item->getstats().DEF), 12, WBOLD, GameManager::LGRAY, Vector2F(dest.x, lastyoriginal), Vector2F(dest.w, 30)));
		lastyoriginal += 30;
		this->stats.push_back(new Text("Fire Rate: +" + std::to_string(item->getstats().DEX) + " shots/s", 12, WBOLD, GameManager::LGRAY, Vector2F(dest.x, lastyoriginal), Vector2F(dest.w, 30)));
		lastyoriginal += 30;
		this->stats.push_back(new Text("Health Regen: +" + std::to_string(item->getstats().VIT) + " HP/s", 12, WBOLD, GameManager::LGRAY, Vector2F(dest.x, lastyoriginal), Vector2F(dest.w, 30)));
		lastyoriginal += 30;
		this->stats.push_back(new Text("Mana Regen: +" + std::to_string(item->getstats().WIS) + " MP/s", 12, WBOLD, GameManager::LGRAY, Vector2F(dest.x, lastyoriginal), Vector2F(dest.w, 30)));
		lastyoriginal += 30;
		this->stats.push_back(new Text("HP Bonus: +" + std::to_string(item->getstats().HP), 12, WBOLD, GameManager::LGRAY, Vector2F(dest.x, lastyoriginal), Vector2F(dest.w, 30)));
		lastyoriginal += 30;
		this->stats.push_back(new Text("MP Bonus: +" + std::to_string(item->getstats().MP), 12, WBOLD, GameManager::LGRAY, Vector2F(dest.x, lastyoriginal), Vector2F(dest.w, 30)));
		lastyoriginal += 30;
		this->stats.push_back(new Text("Visibility Bonus: +" + std::to_string(item->getstats().VIS) + " meters", 12, WBOLD, GameManager::LGRAY, Vector2F(dest.x, lastyoriginal), Vector2F(dest.w, 30)));
		lastyoriginal += 30;
		this->stats.push_back(new Text("Speed Bonus: +" + std::to_string(item->getstats().SPD) + " meters/s", 12, WBOLD, GameManager::LGRAY, Vector2F(dest.x, lastyoriginal), Vector2F(dest.w, 30)));
		lastyoriginal += 30;
	}
	else {
		stats.clear();
	}
}

void ItemDetails::handleEvents(SDL_Event* e) {
	
}