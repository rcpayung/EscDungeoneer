#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Tooltip.h"


class UIComponent {
private:
	Sprite* sprite;
	float scale;
protected:
	SDL_Rect dest;
public:

	// Text Colors	  R   G   B

	UIComponent(int x, int y, int w, int h, float scale);
	virtual void render();
	virtual void update() = 0;
	virtual void clean();
	virtual void handleEvents(SDL_Event* e) = 0;
	
	void setPosition(Vector2F f);
	void setSize(int x, int y);
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


