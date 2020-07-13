#include "Sprite.h"

Sprite::Sprite(const char* path, Vector2F pos, Sizer size, float scale) {
	position = pos;
	this->size = {int(size.W * scale), int(size.H * scale)};
	
	atlas = IMG_Load(path);
	aSize = { atlas->w,atlas->h };
	texture = SDL_CreateTextureFromSurface(GameManager::rd, atlas);
	SDL_FreeSurface(atlas);
	src = {0,0,size.W,size.H};
	dest = {position.X,position.Y,this->size.W,this->size.H};
}

Sprite::Sprite(const char* path, Vector2F pos, Sizer size) {
	position = pos;
	this->size = { int(size.W * GameManager::scale), int(size.H * GameManager::scale) };

	atlas = IMG_Load(path);
	aSize = { atlas->w,atlas->h };
	texture = SDL_CreateTextureFromSurface(GameManager::rd, atlas);
	SDL_FreeSurface(atlas);
	src = { 0,0,size.W,size.H };
	dest = { position.X,position.Y,this->size.W,this->size.H };
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
	SDL_RenderCopyEx(GameManager::rd, texture, &src, &dest,theta,NULL,SDL_FLIP_NONE);
}

void Sprite::clean() {
	SDL_DestroyTexture(texture);
}