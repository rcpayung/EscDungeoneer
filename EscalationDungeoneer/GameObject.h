#pragma once
#include "Sprite.h"
#include <vector>
#include <stdio.h>
#include <iostream>

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

	// Other Attributes:
	std::string name;
	Vector2F position;
public:
	GameObject(SDL_Renderer* rd, std::string name, int x, int y, int w, int h, float scale, std::string path);
	void playAnimation(int id,bool over);
	void addAnimation(int tTime, int sCount, int sX, int sY, bool loop);
	void setPosition(int x, int y);
	Vector2F getPosition();
	void setIdle(int x, int y);
	void update(bool paused);
	void render(float theta);
	void clean();
};

