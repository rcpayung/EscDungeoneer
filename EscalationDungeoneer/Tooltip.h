#pragma once
#include "SDL.h"
#include "Text.h"

class Tooltip {
private:
	std::string tip;
	SDL_Color fore, back;
	int fontweight, fontsize;
	SDL_Renderer* rd;
	Text* text;
	Vector2F position;
	SDL_Rect dest;
public:
	Tooltip(SDL_Renderer* rd, int fontsize, std::string tip, int fontWeight, SDL_Color fore, SDL_Color back, int x, int y);
	void setTip(std::string tip);
	void setPosition(Vector2F p);
	void setPosition(int x, int y);
	void update();
	void render();
	void clean();
};

