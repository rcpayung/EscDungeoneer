#pragma once
#include "GameObject.h"
#include "Item.h"

class Player : public GameObject {
private:
	int HP, MaxHP, MP, MaxMP, level, TotalXP, LevelXP;
	float VelX, VelY;
	Statistics stats;
	Sprite* sprite;
public:
	Player(std::string name, Vector2F p, float scale);
	void setVelocityX(float vel);
	void setVelocityY(float vel);

	void update();
	void handleEvents(SDL_Event* e);

};

