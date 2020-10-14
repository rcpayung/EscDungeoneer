#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "Vector2F.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"

class Sprite2D {
private:
	SDL_Surface* atlas;
	SDL_Texture* tex;
	SDL_Rect src, dest, resetD;
	int atlasX, atlasY;
	Vector2F position;

public:
	Sprite2D(const char * path, int x, int y, float scale);
	void setCurrentImageBounds(int x, int y);
	void setPosition(Vector2F p);
	void setPosition(int x, int y);
	void setScale(float scale);
	void resetScale();
};

