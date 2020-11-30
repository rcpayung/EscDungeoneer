#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2F.h"
#include "GameManager.h"

struct Animation {
	Uint16 animtime = 1;
	bool loop = false;
	bool playing = false;
	Vector2F startFrame;
	Uint16 numFrames;
	Uint16 elapsedFrames = 0;
	Uint16 duration;
};

class Sprite {
private:
	std::vector<Animation> anims;
	Animation* cAnim;
	SDL_Surface* atlas;
	SDL_Texture* texture;
	std::string name;
	SDL_Rect source,
		dest;
	SDL_Point center;

	float scale = 1.0f,
		theta = 0.0f;

	Vector2F loc;
	Vector2F size,
		scaleSize,
		atlasSize;

public:
	Sprite(const char* name, const char* file, Vector2F loc, Vector2F size, float scale);
	//Sprite(const Sprite& sp) : (sp->file, sp->loc, sp->size, sp->scale);
	~Sprite();
	
	const Vector2F getSize() const;
	const Vector2F getASize() const;
	const Vector2F getScaledSize() const;

	bool addAnimation(Animation anim);
	bool playAnimation(size_t animID);
	bool pauseAnimation();
	bool cancelAnimation();
	bool removeAnimation(size_t animID);
	bool resetAnimation();

	bool setImage(Vector2F atlasLoc);
	bool setScale(float scale);
	bool setScale(int x, int y);

	bool setPosition(int x, int y);	
	bool setPosition(Vector2F pos);
	void setRotation(float theta);

	void update();
	void render();
	void clean();

	std::string to_string() const;
};











