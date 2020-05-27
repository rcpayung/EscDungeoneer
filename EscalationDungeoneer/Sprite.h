#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2F.h"

struct Sizer {
	int W, H;
};

class Sprite {

private:
	SDL_Surface* atlas;
	SDL_Texture* texture;
	SDL_Renderer* rd;
	SDL_Rect src, dest;
	float scale;
	Vector2F position;
	Sizer size, aSize;
public:
	Sprite(SDL_Renderer* rd, std::string path, int x, int y, int w, int h, float scale);
	void setScale(float scale);
	void setPosition(int x, int y);
	void setImage(int x, int y);
	Sizer getSize();
	Sizer getAtlas();
	void render(float theta);
	void clean();
};

