#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include "Vector2F.h"
#include <iostream>
#include <stdio.h>

enum weight {
	WNORMAL,
	WBOLD,
	WITALIC,
	WBITALIC
};

enum color {
	WHITE,
	LIGHTGRAY,
	GRAY,
	DARKGRAY,
	BLACK,
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	INDIGO,
	VIOLET,
	PURPLE,
	PINK,
	BROWN,
	L_BROWN
};

class Text {
private:
	TTF_Font* font;
	SDL_Color color;
	SDL_Texture* tex;
	SDL_Rect pos, bounds;
	SDL_Renderer* rd;
	SDL_Surface* surf;
	short fontSize;
	
public:
	Text(SDL_Renderer* rd, std::string message, short fontsize, int fontWeight, SDL_Color color, Vector2F pos, Vector2F size);
	void render();
	void clean();
	void setColor(SDL_Color color);
	SDL_Texture* loadTexture(std::string message, SDL_Color color);
	void setText(std::string message);
	void setCenter();
	void setBounds(int x, int y, int w, int h);
};
