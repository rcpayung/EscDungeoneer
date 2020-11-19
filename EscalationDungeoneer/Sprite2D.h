#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "Vector2F.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"

struct Animation {
	// Beginning frame, ending frame, the duration of the animation in (MS) (e.g. 1000MS = 1 second)
	int beginFrame, nFrames, duration;
	// If the animation can be cancelled by another activating:
	bool cancellable;
};

class Sprite2D {
private:
	SDL_Surface* atlas;
	SDL_Texture* tex;
	SDL_Rect src, dest, resetD;
	int atlasX, atlasY, sX, sY;
	Vector2F position;
	Animation* playable;
	Animation anims[25];
	Uint8 lastEmpty = 0;

public:
	Sprite2D(const char * path, int sX, int sY, float scale);
	void setCurrentImageBounds(int x, int y);
	void setPosition(Vector2F p);
	void setPosition(int x, int y);
	void setScale(float scale);
	void resetScale();
	bool animate(int beginFrame, int nFrames, int duration, bool cancellable);
	bool set_animate(int id);
	bool cancel_animate();
	void update();
	void play_animate();
	void render(float theta, SDL_Point center, SDL_RendererFlip flip);
	void clean();
};

