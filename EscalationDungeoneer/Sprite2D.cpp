#include "Sprite2D.h"

Sprite2D::Sprite2D(const char* path, int sX, int sY, float scale) {
	this->atlas = IMG_Load(path);
	this->atlasX = atlas->w;
	this->atlasY = atlas->h;
	this->sX = sX;
	this->sY = sY;
	this->src = { 0, 0, sX, sY };
	this->dest = { 0, 0, sX, sY };
	this->dest = { 0, 0, int(sX * scale), int(sY * scale) };
	this->playable = nullptr;
	

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

void Sprite2D::update() {
	if (playable != nullptr) {
		play_animate();
	}
}

void Sprite2D::setCurrentImageBounds(int x, int y) {
	this->src.x = x;
	this->src.y = y;
}

void Sprite2D::setPosition(Vector2F p) {
	this->dest.x = p.X;
	this->dest.y = p.Y;
	this->position = p;
}

void Sprite2D::setPosition(int x, int y) {
	this->dest.x = x;
	this->dest.y = y;
}

bool Sprite2D::animate(int beginFrame, int nFrames, int duration, bool cancellable) {
	for (Animation i : anims) {
		if (i.beginFrame == beginFrame && i.nFrames == nFrames && i.duration == duration) {
			return false;
			// Duplicate animation setting.
		}
	}
	this->anims[lastEmpty] = Animation{ beginFrame,nFrames,duration,cancellable };
	lastEmpty += 1;
	return true;
}

void Sprite2D::play_animate() {
	
}

bool Sprite2D::set_animate(int id) {
	if (id == -1) return cancel_animate();
	if (playable != nullptr) {
		playable = &anims[id];
		return true;
	}
	else
		return false;
}

bool Sprite2D::cancel_animate() {
	if (playable != nullptr && playable->cancellable) {
		playable = nullptr;
		return true;
	}
	else {
		return false;
	}
}

void Sprite2D::render(float theta,SDL_Point center,SDL_RendererFlip flip) {
	SDL_RenderCopyEx(GameManager::rd, tex, &src, &dest, theta, &center, flip);
}

void Sprite2D::clean() {
	set_animate(-1);
	SDL_DestroyTexture(tex);
}