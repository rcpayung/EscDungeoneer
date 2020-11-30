#include "Sprite.h"

Sprite::Sprite(const char* name, const char* file, Vector2F loc, Vector2F size, float scale) {
	this->name = name;
	this->loc = loc;
	this->size = size;
	this->atlas = IMG_Load(file);
	this->atlasSize = Vector2F(atlas->w, atlas->h);
	this->texture = SDL_CreateTextureFromSurface(GameManager::rd, atlas);
	SDL_FreeSurface(atlas);
	this->scaleSize = Vector2F(int(size.X * scale), int(size.Y * scale));

	this->source = { 0, 0, this->size.X, this->size.Y };
	this->dest = { loc.X,loc.Y,this->size.X,this->size.Y };
	this->cAnim = nullptr;
	
	this->center.x = loc.X + int(size.X / 2);
	this->center.y = loc.Y + int(size.Y / 2);

}

Sprite::~Sprite() {

}

bool Sprite::setScale(int x, int y) {
	this->dest.w = x;
	this->dest.h = y;
	this->scaleSize = Vector2F(dest.w, dest.h);
	printf("(%d, %d)\n", this->dest.w, this->dest.h);
	return true;
}

bool Sprite::setScale(float scale) {
	this->scale = scale;
	this->dest.w = int(this->size.X * scale);
	this->dest.h = int(this->size.Y * scale);
	this->scaleSize = Vector2F(dest.w, dest.h);
	printf("%s: (%d, %d)\n", this->name.c_str(), this->dest.w, this->dest.h);
	return true;
}

bool Sprite::setImage(Vector2F atlasLoc) {
	this->source.x = atlasLoc.X;
	this->source.y = atlasLoc.Y;
	return true;
}

void Sprite::update() {
	this->center.x = loc.X + int(scaleSize.X / 2);
	this->center.y = loc.Y + int(scaleSize.Y / 2);

	if (cAnim != nullptr && !GameManager::paused) {
		// update Animation here.
		if (cAnim->animtime != cAnim->duration - 1) {
			if (cAnim->playing) {
				if (cAnim->animtime % int(cAnim->duration / cAnim->numFrames) == 0 && cAnim->elapsedFrames != cAnim->numFrames) {
					if (source.x + size.X >= atlasSize.X - size.X + 1) {
						source.y += size.Y; // Shouldnt need to worry about this since the frames elapsed will reach the maximum before reaching this.
						source.x = 0;
					}
					else {
						source.x += size.X;
					}
					cAnim->elapsedFrames++;
				}
				cAnim->animtime++;
			}
		}
		else {
			cAnim->loop ? resetAnimation() : cancelAnimation();
		}
	}
}

bool Sprite::resetAnimation() {
	if (this->cAnim != nullptr) {
		this->cAnim->animtime = 1;
		this->cAnim->elapsedFrames = 0;
		source.x = cAnim->startFrame.X * size.X;
		source.y = cAnim->startFrame.Y * size.Y;
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
	if (cAnim != nullptr) {
		return false;
	}
	if (animID < 0 || animID > this->anims.size() - 1) {
		return false;
	}
	printf("Playing Animation\n");
	this->cAnim = &this->anims[animID];
	this->cAnim->playing = true;
	this->setImage(cAnim->startFrame);
	return true;
}

bool Sprite::addAnimation(Animation anim) {
	for (Animation i : this->anims) {
		if (i.startFrame == anim.startFrame) {
			printf("Duplicate Animation.\n");
			return false;
		}
	}
	this->anims.push_back(anim);
	return true;
}

bool Sprite::removeAnimation(size_t animID) {
	if (this->anims.empty() || animID > this->anims.size() - 1) return false;
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

const Vector2F Sprite::getASize() const {
	return this->atlasSize;
}

const Vector2F Sprite::getSize() const {
	return this->size;
}

const Vector2F Sprite::getScaledSize() const {
	return this->scaleSize;
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

std::string Sprite::to_string() const {
	return this->name + " : " + this->loc.to_string() + ", SIZE: " + this->size.to_string() + ", ATLAS_SIZE: " + this->atlasSize.to_string() + ", SCALE: " + std::to_string(this->scale) + ", ROTATION: " + std::to_string(this->theta) + " degrees.";
}
