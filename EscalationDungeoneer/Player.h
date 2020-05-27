#pragma once
#include "GameObject.h"
class Player : public GameObject {
private:
	int HP, MaxHP, MP, MaxMP, level, TotalXP, LevelXP;
	float speed, velocity;

public:
	Player(SDL_Renderer* rd, std::string name, Vector2F p, float scale);
};

