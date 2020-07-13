#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2F.h"
#include "GameManager.h"

struct Sizer {
	int W, H;
};

class Sprite {

private:
	SDL_Surface* atlas;
	SDL_Texture* texture;
	SDL_Rect src, dest;
	float scale;
	Vector2F position;
	Sizer size, aSize;
public:
	Sprite(const char* path, Vector2F pos, Sizer size);
	Sprite(const char* path, Vector2F pos, Sizer size, float scale);
	void setScale(float scale);
	void setPosition(int x, int y);
	void setImage(int x, int y);
	Sizer getSize();
	Sizer getAtlas();
	void render(float theta);
	void clean();
};

