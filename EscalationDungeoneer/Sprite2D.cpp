#include "Sprite2D.h"

Sprite2D::Sprite2D(const char* path, int x, int y, float scale) {
	this->atlas = IMG_Load(path);
	this->atlasX = atlas->w;
	this->atlasY = atlas->h;

	tex = SDL_CreateTextureFromSurface(GameManager::rd, atlas);
	SDL_FreeSurface(atlas);
}


void Sprite2D::setScale(float scale) {
	this->dest.w = dest.w * scale;
	this->dest.h = static_cast<int>(dest.h * scale);
}

void Sprite2D::resetScale() {
	this->dest.w = resetD.w;
	this->dest.h = resetD.h;
}


void Sprite2D::setCurrentImageBounds(int x, int y) {
	this->dest.x = x;
	this->dest.y = y;
}

void Sprite2D::setPosition(Vector2F p) {

}

void Sprite2D::setPosition(int x, int y) {

}