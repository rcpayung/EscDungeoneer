#include "Sprite.h"

Sprite::Sprite(const char* name, const char* file, Vector2F loc, Vector2F size, float scale) {
	this->name = name;
	this->loc = loc;
	this->size = size;
	this->atlas = IMG_Load(file);
	this->atlasSize = Vector2F(atlas->w, atlas->h);
	this->texture = SDL_CreateTextureFromSurface(GameManager::rd, atlas);
	SDL_FreeSurface(atlas);

	this->source = { 0, 0, this->size.X, this->size.Y };
	this->dest = { loc.X,loc.Y,this->size.X,this->size.Y };
	this->cAnim = nullptr;
}

Sprite::~Sprite() {

}



bool Sprite::setScale(int x, int y) {
	if (x < 0 || y < 0)
		return false;
	this->dest.w = x;
	this->dest.h = y;
	return true;
}

bool Sprite::setScale(float scale) {
	if (scale < 0.0f || scale > 10.0f)
		return false;
	this->scale = scale;
	this->dest.w = static_cast<int>(this->size.X * scale);
	this->dest.h = static_cast<int>(this->size.Y * scale);
	return true;
}

bool Sprite::setImage(Vector2F atlasLoc) {
	int x = static_cast<int>(atlasLoc.X * size.X);
	int y = static_cast<int>(atlasLoc.Y * size.Y);

	if (x < 0 || x >(this->atlasSize.X - this->size.X + 1) || y < 0 || y >(this->atlasSize.Y - this->size.Y + 1))
		return false;
	else {
		this->source.x = x;
		this->source.y = y;
		return true;
	}
}

void Sprite::update() {
	if (cAnim != nullptr) {
		// update Animation here.
		if (cAnim->animtime != cAnim->duration && cAnim->playing != false) {
			int currentX = source.x;
			int currentY = source.y;
			if ((cAnim->animtime % (cAnim->duration / cAnim->numFrames) == 0)) {
				if (currentX + size.X < (atlas->w - size.X + 1)) {
					if (currentY + size.Y < (atlas->h - size.Y + 1)) {
						currentY += size.Y;
						currentX = 0;
					}
				}
				this->setImage(Vector2F(currentX, currentY));
			}
			cAnim->animtime++;
		}
		else {
			cAnim->loop ? resetAnimation() : cancelAnimation();
		}
	}
}

bool Sprite::resetAnimation() {
	if (this->cAnim != nullptr) {
		this->cAnim->animtime = 0;
		this->setImage(this->cAnim->startFrame * this->size);
		return true;
	}
	return false;
}

bool Sprite::cancelAnimation() {
	if (this->cAnim != nullptr) {
		resetAnimation();
		this->setImage(Vector2F(0, 0));
		this->cAnim = nullptr;
		return true;
	}
	printf("Cannot cancel animation. No Animation is set.\n");
	return false;
}

bool Sprite::pauseAnimation() {
	if (this->cAnim != nullptr) {
		if (this->cAnim->playing) {
			this->cAnim->playing = false;
		}
		else {
			this->cAnim->playing = true;
		}
		return true;
	} 
	return false;
}

bool Sprite::playAnimation(size_t animID) {
	if (animID < 0 || animID > this->anims.size()) {
		return false;
	}
	printf("Playing Animation\n");
	this->cAnim = &this->anims[animID];
	this->cAnim->playing = true;
	return true;
}

bool Sprite::addAnimation(Animation anim) {
	for (Animation i : this->anims) {
		if (i.startFrame == anim.startFrame) {
			printf("Duplicate Animation. ID: %d\n",i);
			return false;
		}
	}
	this->anims.push_back(anim);
	return true;
}

bool Sprite::removeAnimation(size_t animID) {
	if (this->anims.empty() || animID > this->anims.size()) return false;
	else {
		for (size_t i = 0; i < anims.size(); i++) {
			if (i >= animID and i < anims.size()-1) {
				anims[i] = anims[i + 1];
			}
		}
		anims.pop_back();
		return true;
	}
}

Vector2F Sprite::getASize() const {
	return this->atlasSize;
}

Vector2F Sprite::getSize() {
	return this->size;
}

bool Sprite::setPosition(int x, int y) {
	if (x < 0 || y < 0) {
		return false;
	}
	this->loc = Vector2F(x, y);
	this->dest.x = x;
	this->dest.y = y;
	return true;
}

bool Sprite::setPosition(Vector2F pos) {
	return this->setPosition(pos.X, pos.Y);
}

void Sprite::setRotation(float theta) {
	this->theta = theta;
}

void Sprite::render() {
	SDL_RenderCopy(GameManager::rd, texture, &source, &dest);
}

void Sprite::clean() {
	SDL_DestroyTexture(texture);
}

const char* Sprite::to_string() const {
	std::string result = this->name;
	result.append(" : ");
	result.append(this->loc.to_string());
	result.append(", SIZE: ");
	result.append(this->size.to_string());
	result.append(", ATLAS_SIZE: ");
	result.append(this->atlasSize.to_string());
	result.append(", SCALE: ");
	result.append(std::to_string(scale));
	result.append(", ROTATION: ");
	result.append(std::to_string(this->theta));
	return result.c_str();
}
