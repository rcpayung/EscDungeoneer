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
	void setMaxHP(int HP);
	void setHP(int HP);
	
	void setMaxMP(int MP);
	void setMP(int MP);

	void levelUp();
	
	void setSpeed(float speed);

	void setATT(int amount);
	void setDEF(int amount);
	void setVIT(int amount);
	void setWIS(int amount);
	void setDEX(int amount);

	void update();
	void handleEvents(SDL_Event e);

};

