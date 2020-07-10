#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Tooltip.h"


class UIComponent {
private:
	Sprite* sprite;
	float scale;
protected:
	SDL_Renderer* rd;
	SDL_Rect dest;
public:

	// Text Colors	  R   G   B
	SDL_Color WHITE{ 255,255,255, 255 };
	SDL_Color GREEN{ 100,200,100, 255 };
	SDL_Color LGRAY{ 200,200,200, 255 };
	SDL_Color L_BLU{ 20, 90,150, 255 };
	SDL_Color L_RED{ 150, 25, 25, 255 };
	SDL_Color GRAY{ 140,140,140, 255 };
	SDL_Color D_GRE{ 20, 50, 20, 255 };
	SDL_Color DGRAY{ 25, 25, 25, 255 };
	SDL_Color BLACK{ 0,  0,  0, 255 };

	UIComponent(SDL_Renderer* rd, int x, int y, int w, int h, float scale);
	virtual void render();
	virtual void update() = 0;
	virtual void clean();
	virtual void handleEvents(SDL_Event* e) = 0;
	
	void setPosition(Vector2F f);
	void setPosition(int x, int y);
	Vector2F getPosition() {
		return Vector2F(dest.x, dest.y);
	}
	Vector2F getSize() {
		return Vector2F(dest.w, dest.h);
	}
	void setSprite(const char* asset);
	void setScale(float scale);
	float getScale();
};


