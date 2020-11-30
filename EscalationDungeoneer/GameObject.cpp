#include "GameObject.h"

size_t GameObject::GameObjectIDS = 0;

GameObject::GameObject(const char* name, Vector2F loc, Vector2F size) {
	GameObject::GameObjectIDS++;
	this->thisID = GameObjectIDS;
	this->loc = loc;
	this->name = name;
	this->size = size;
	printf("%s\n", size.to_string().c_str());
	this->hovering = false;
	this->focused = false;
	this->tip = new Tooltip(15, "GameObject", WNORMAL, GameManager::WHITE, GameManager::DGRAY, loc.X, loc.Y);
}

void GameObject::pushSprite(Sprite* sprite) {
	this->sprites.push_back(sprite);
}

bool GameObject::removeSprite(size_t SpriteID) {
	if (this->sprites.empty() || SpriteID > this->sprites.size()) return false;
	else {
		for (size_t i = 0; i < this->sprites.size(); i++) {
			if (i >= SpriteID and i < this->sprites.size() - 1) {
				this->sprites[i] = this->sprites[i + 1];
			}
		}
		this->sprites.pop_back();
		return true;
	}
}

const Sprite* GameObject::getSprite(size_t ID) const {
	if (sprites.empty() || ID > sprites.size()) return nullptr;
	else return this->sprites[ID];
}

bool GameObject::addAnimation(size_t SpriteID, Animation anim) {
	if (this->sprites.empty() || SpriteID > this->sprites.size()) return false;
	else return this->sprites[SpriteID]->addAnimation(anim);
}

bool GameObject::removeAnimation(size_t SpriteID, size_t animID) {
	if (this->sprites.empty() || SpriteID > this->sprites.size()) return false;
	else return this->sprites[SpriteID]->removeAnimation(animID);
}

bool GameObject::playAnimation(size_t SpriteID, size_t animID) {
	if (this->sprites.empty() || SpriteID > this->sprites.size()) return false;
	else return this->sprites[SpriteID]->playAnimation(animID);
}

bool GameObject::pauseAnimation(size_t SpriteID) {
	if (this->sprites.empty() || SpriteID > this->sprites.size()) return false;
	else return this->sprites[SpriteID]->pauseAnimation();
}

bool GameObject::cancelAnimation(size_t SpriteID) {
	if (this->sprites.empty() || SpriteID > this->sprites.size()) return false;
	else return this->sprites[SpriteID]->cancelAnimation();
}

bool GameObject::setSpritePos(size_t SpriteID, int x, int y) {
	if (this->sprites.empty() || SpriteID > this->sprites.size()) return false;
	else {
		this->sprites[SpriteID]->setPosition(Vector2F(x, y));
		return true;
	}
}

bool GameObject::setSpritePos(size_t SpriteID, Vector2F loc) {
	if (this->sprites.empty() || SpriteID > this->sprites.size()) return false;
	else {
		this->sprites[SpriteID]->setPosition(loc);
		return true;
	}
}

bool GameObject::setScale(float scale) {
	if (scale < 0.25f || scale > 10.0f) {
		printf("Failure to scale.\n");
		return false;
	}
	printf("Reaching this point.\n");
	this->size.X = static_cast<int>(size.X * scale);
	this->size.Y = static_cast<int>(size.Y * scale);
	printf("From GameObject: ID: %d, %s\n", int(this->getID()), this->getSize().to_string().c_str());
	for (size_t i = 0; i < sprites.size(); i++) {
		sprites[i]->setScale(scale);
	}
	return true;
}

void GameObject::render() {
	for (Sprite* i : this->sprites) {
		i->render();
	}
	if (GameManager::devMode && this->focused) {
		tip->render();
	}
}

void GameObject::update() {
	this->center.x = this->getSize().X / 2;
	this->center.y = this->getSize().Y / 2;
	for (Sprite* i : this->sprites) {
		i->update();
	}
	this->tip->setTip(this->to_string());
	this->tip->update();
}

void GameObject::clean() {

	for (Sprite* i : this->sprites) {
		i->clean();
	}
	tip->clean();

}

bool GameObject::setPosition(Vector2F loc) {
	if (loc.X < 0 || loc.Y < 0) return false;
	else {
		for (Sprite* i : this->sprites) {
			i->setPosition(loc);
		}
		this->loc = loc;
		this->tip->setPosition(loc.X - (tip->getWidth() / 2),loc.Y - 40);
		return true;
	}
}

Vector2F GameObject::getPosition() const {
	return this->loc;
}

const size_t GameObject::getID() const {
	return this->thisID;
}

std::string GameObject::getName() const {
	return this->name;
}

const Vector2F GameObject::getSize() const {
	return this->size;
}

std::string GameObject::to_string() const {
	return "GameObject: " + this->getName() + ", ID: " + std::to_string(this->getID()) + ", Loc: " + this->getPosition().to_string() + ", Size: " + this->getSize().to_string();
}

bool GameObject::handleCollisions(GameObject* b) {
	// Bottom Collision:
	SDL_Rect collRect;

	// Bottom:
	return false;
	
}

void GameObject::handleEvents(SDL_Event* e) {
	if (GameManager::mx > this->getPosition().X && GameManager::mx < (this->getPosition().X + this->getSize().X)) {
		if (GameManager::my > this->getPosition().Y && GameManager::my < (this->getPosition().Y + this->getSize().Y)) {
			if (!GameManager::inInventory && !GameManager::paused)
				this->hovering = true;
			else {
				hovering = false;
			}
		}
		else {
			hovering = false;
		}
	}
	else {
		hovering = false;
	}
	switch (e->type) {
	case SDL_MOUSEBUTTONDOWN:
		switch (e->button.button) {
		case SDL_BUTTON_LEFT:
			hovering ? focused = true : focused = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}