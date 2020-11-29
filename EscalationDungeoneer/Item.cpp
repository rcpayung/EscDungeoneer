#include "Item.h"

Item::Item(std::string name, float scale, const char* spritepath, bool stackable) : GameObject(name.c_str(), Vector2F( 0,0 ), Vector2F( 48,48 )) {
	this->stackable = stackable;
	stacksize = 1;
	Sprite* sprite = new Sprite(name.c_str(), spritepath, Vector2F(0, 0), Vector2F(64,64),1.0f);
	sprite->setScale(48, 48);
	this->pushSprite(sprite);
	this->l_stack = new Text(std::to_string(stacksize), 10, WBOLD, GameManager::GOLD, Vector2F(this->getPosition().X, this->getPosition().Y), Vector2F(15,15));
	l_stack->setCenter();
	l_stack->setMiddle();
	this->name = name;
}


void Item::setPosition(Vector2F p) {
	__super::setPosition(p);
}

void Item::setPosition(int x, int y) {
	__super::setPosition(Vector2F(x,y));
}

void Item::setStats(Statistics stats) {
	this->stats = stats;
}

Statistics Item::getstats() {
	return this->stats;
}

void Item::setTooltip(std::string message) {
	SDL_Color color = GameManager::LGRAY;
	
	if (this->getRarityString() == "Uncommon") {
		color = GameManager::UNCOMMON;
	}
	else if (this->getRarityString() == "Rare") {
		color = GameManager::RARE;
	}
	else if (this->getRarityString() == "Very Rare") {
		color = GameManager::VERYRARE;
	}
	else if (this->getRarityString() == "Legendary") {
		color = GameManager::LEGENDARY;
	}
	else if (this->getRarityString() == "Godly") {
		color = GameManager::GOLD;
	}


	this->t = new Tooltip(12, message, WNORMAL, color, GameManager::DGRAY, GameManager::mx + 30, GameManager::my + 30);
}

void Item::showToolTip() {
	t->render();
}

void Item::update() {
	this->l_stack->setText(std::to_string(stacksize));
	this->l_stack->setBounds(this->getPosition().X, this->getPosition().Y, 15, 15);
	this->l_stack->setMiddle();
	this->l_stack->setCenter();
	this->t->setPosition(Vector2F(GameManager::mx + 30, GameManager::my + 30));
	this->t->update();
}

bool Item::is_stackable() {
	return this->stackable;
}

int Item::getStack() {
	return this->stacksize;
}

void Item::increase_stack(int amount) {
	this->stacksize += amount;
}

void Item::render() {
	__super::render();
	if (stacksize > 1) l_stack->render();
}

void Item::clean() {
	__super::clean();
}

void Item::handleEvents(SDL_Event* e) {
	__super::handleEvents(e);
	switch (e->type) {
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (e->button.button) {
		case SDL_BUTTON_LEFT:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

std::string Item::getName() {
	return this->name;
}

void Item::generateRarity(float modifier) {
	int generation = std::rand() % 15000;
	printf("%d\n", generation);

	if (generation >= 5000 && generation < 10000 * modifier) {
		this->rarity = Rarity::UNCOMMON;
	}
	else if (generation >= 10000 * modifier && generation < 13000 * modifier) {
		this->rarity = Rarity::RARE;
	}
	else if (generation >= 13000 * modifier && generation < 14500 * modifier) {
		this->rarity = Rarity::VERY_RARE;
	}
	else if (generation >= 14500 * modifier && generation < 14800 * modifier) {
		this->rarity = Rarity::LEGENDARY;
	}
	else if (generation >= 14800 * modifier) {
		this->rarity = Rarity::GODLY;
	}
	else {
		rarity = Rarity::COMMON;
	}
	switch (rarity) {
	case Rarity::COMMON:
		printf("COMMON GENERATED\n");
		break;
	case Rarity::UNCOMMON:
		printf("UNCOMMON GENERATED\n");
		break;
	case Rarity::RARE:
		printf("RARE GENERATED\n");
		break;
	case Rarity::VERY_RARE:
		printf("VERY RARE GENERATED\n");
		break;
	case Rarity::LEGENDARY:
		printf("LEGENDARY GENERATED\n");
		break;
	case Rarity::GODLY:
		printf("GODLY GENERATED\n");
		break;
	}
}

void Item::setRarity(Rarity rare) {
	this->rarity = rare;
}

std::string Item::getRarityString() {
	switch (this->rarity) {
	case Rarity::COMMON:
		return "Common";
		break;
	case Rarity::UNCOMMON:
		return "Uncommon";
		break;
	case Rarity::RARE:
		return "Rare";
		break;
	case Rarity::VERY_RARE:
		return "Very Rare";
		break;
	case Rarity::LEGENDARY:
		return "Legendary";
		break;
	case Rarity::GODLY:
		return "Godly";
		break;
	default:
		return "Common";
		break;
	}
}

Rarity Item::getRarity() {
	return this->rarity;
}


void Item::setItemType(ItemType type) {
	this->type = type;
}

void Item::setWeaponType(WeaponType type) {
	this->w_type = type;
}

void Item::setArmorType(ArmorType type) {
	this->a_type = type;
}