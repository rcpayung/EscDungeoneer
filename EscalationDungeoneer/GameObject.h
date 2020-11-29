#pragma once
#include "Sprite.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include "GameManager.h"
#include "Tooltip.h"

class GameObject {
private:
	std::vector<Sprite*> sprites;
	Vector2F loc, size;
	size_t thisID;
	std::string name;
	bool hovering, focused;
	Tooltip* tip;
	SDL_Point center;
	float rotation = 0.0f;
protected:
	static size_t GameObjectIDS;
public:
	GameObject(const char* name, Vector2F loc, Vector2F size);
	void pushSprite(Sprite* sprite);
	bool removeSprite(size_t SpriteID);
	const Sprite* getSprite(size_t ID) const;

	bool addAnimation(size_t SpriteID, Animation anim);
	bool removeAnimation(size_t SpriteID, size_t animID);
	bool playAnimation(size_t SpriteID, size_t animID);
	bool pauseAnimation(size_t SpriteID);
	bool cancelAnimation(size_t SpriteID);

	bool setSpritePos(size_t SpriteID, int x, int y);
	bool setSpritePos(size_t SpriteID, Vector2F loc);

	bool setScale(float scale);

	void update();
	void render();
	void clean();

	bool setPosition(Vector2F loc);
	Vector2F getPosition() const;

	const size_t getID() const;
	std::string getName() const;
	const Vector2F getSize() const;

	void handleEvents(SDL_Event* e);
	std::string to_string() const;
	bool handleCollisions(GameObject* b);
};
