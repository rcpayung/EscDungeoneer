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
	Vector2F position, size;
	float rotation, scale;
	bool paused;
public:
	static int ID;
	GameObject(SDL_Renderer* rd, std::string name, int x, int y, int w, int h, float scale, std::string path);
	
	// Animation Functions
	void playAnimation(int id,bool over);
	void addAnimation(int tTime, int sCount, int sX, int sY, bool loop);
	void setIdle(int x, int y);

	// Game Functions
	void update(bool paused);
	void render();
	void clean();

	// Positional Functions
	void setPosition(int x, int y);
	void setRotation(float theta);
	void setScale(float scale);

	Vector2F getPosition();
	Vector2F getSize();
	float getTheta();
	
	static int getID();
};

