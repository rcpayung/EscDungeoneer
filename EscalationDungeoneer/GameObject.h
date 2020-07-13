#pragma once
#include "Sprite.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include "GameManager.h"
#include "Tooltip.h"

struct Animation {
	int tTime;
	int cTime = 0;
	int sCount;
	int counted;
	int sX, sY, oX, oY;
	bool loop = false;
};


class GameObject {
private:
	// Sprite Attributes:
	Sprite* sprite;
	Vector2F idle;
	// Animation Attributes:
	std::vector<Animation> anims;
	Animation* cAnim;
	bool hovering, focus;
	// Other Attributes:
	std::string name;
	Vector2F position; 
	Sizer size;
	float rotation, scale;
	Tooltip* tip;
public:
	static int ID;
	GameObject(std::string name, Vector2F pos, Sizer size, const char* path);
	
	// Animation Functions
	void playAnimation(int id,bool over);
	void addAnimation(int tTime, int sCount, int sX, int sY, bool loop);
	void setIdle(int x, int y);

	// Game Functions
	void update();
	void render();
	void clean();

	// Positional Functions
	void setPosition(int x, int y);
	void setRotation(float theta);
	void setScale(float scale);

	Vector2F getPosition();
	Sizer getSize();
	float getTheta();
	
	static int getGID();
	void handleEvents(SDL_Event* event);
};

