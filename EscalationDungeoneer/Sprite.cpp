#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* rd, std::string path, int x, int y, int w, int h, float scale) {
	position = Vector2F(x,y);
	this->rd = rd;
	size = {w, h};
	// Load atlas
	atlas = IMG_Load(path.c_str());
	// set the atlas size to the size of the loaded atlas.
	aSize = {atlas->w, atlas->h};
	// Create the texture atlas
	texture = SDL_CreateTextureFromSurface(rd, atlas);
	// Free up the atlas surface
	SDL_FreeSurface(atlas);
	// set the bounds
	src = {
		0,0,
		w,h
	};
	// set the destination and scale.
	dest = {
		position.X, position.Y,
		int(w * scale), int(h * scale)
	};
}


void Sprite::setScale(float scale) {
	// set the scale of the sprite
	// 1.0 is 100%.
	this->scale = scale;
	this->dest = {
		position.X,
		position.Y,
		int(size.W * scale),
		int(size.H * scale)
	};
}

Sizer Sprite::getSize() {
	return this->size;
}

Sizer Sprite::getAtlas() {
	return this->aSize;
}

void Sprite::setPosition(int x, int y) {
	this->position.X = x;
	this->position.Y = y;

	this->dest = {
		position.X,
		position.Y,
		size.W,
		size.H
	};
}

void Sprite::setImage(int x, int y) {
	this->src = {
		x,
		y,
		size.W,
		size.H
	};
}

void Sprite::render(float theta) {
	SDL_RenderCopyEx(rd, texture, &src, &dest,theta,NULL,SDL_FLIP_NONE);
}

void Sprite::clean() {
	SDL_DestroyTexture(texture);
}