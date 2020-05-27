#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* rd, std::string name, int x, int y, int w, int h, float scale, std::string path) {
	this->sprite = new Sprite(rd, path, x, y, w, h, scale);
	this->position = Vector2F(x, y);
	this->size = Vector2F(w, h);
	this->rotation = 0.0f;
	this->scale = scale;

}
// Play an existing animation with the current id. If over is set to true, it will override any currently playing animation.
void GameObject::playAnimation(int id, bool over) {
	if (anims.size() < id || anims.empty() || id < 0 && !over) {
		printf("No animation of that ID exists for the current gameobject: %s. Either the ID is lower than 1 or there was not an additional added animation. Please verify.",this->name.c_str());
		return;
	}
	else if (cAnim != nullptr) {
		return;
	}
	cAnim = &anims[id];
}

void GameObject::addAnimation(int tTime, int sCount, int sX, int sY, bool loop) {
	Animation anim;
	anim.tTime = tTime;
	anim.cTime = 0;
	anim.sCount = sCount + 1;
	anim.counted = 1;
	anim.sX = sX;
	anim.sY = sY;
	anim.oX = sX;
	anim.oY = sY;
	anim.loop = loop;

	anims.push_back(anim);
}

void GameObject::setIdle(int x, int y) {
	this->idle.X = x;
	this->idle.Y = y;
}

void GameObject::setPosition(int x, int y) {
	if (!paused) {
		this->position = Vector2F(x, y);
		sprite->setPosition(x, y);
	}
}

void GameObject::update(bool paused) {
	if (paused) this->paused = true;
	if (!paused) this->paused = false;
	if (!paused) {
		if (cAnim != nullptr) {
			if (cAnim->cTime % (cAnim->tTime / cAnim->sCount) == 0) {
				if (cAnim->cTime != 0) {
					if (cAnim->counted < cAnim->sCount)
						// If we have not reached the atlas width with our current sprites:
						if (cAnim->sX + sprite->getSize().W != sprite->getAtlas().W) {
							cAnim->sX = cAnim->sX + sprite->getSize().W;

						}
						else {
							cAnim->sY = cAnim->sY + sprite->getSize().H;
							cAnim->sX = 0;
						}
				}
				cAnim->counted++;
				sprite->setImage(cAnim->sX, cAnim->sY);
			}
			// Increment current elapsed time on animation:
			cAnim->cTime++;

			// Reset animation if the loop is true.
			if (cAnim->cTime >= cAnim->tTime && cAnim->loop) {
				cAnim->cTime = 0;
				// Set back to original state.
				sprite->setImage(idle.X, idle.Y);
				cAnim->sX = cAnim->oX;
				cAnim->sY = cAnim->oY;
				cAnim->counted = 1;
			}
			// if animation is finished, set nullptr.
			if (cAnim->counted == cAnim->sCount && cAnim->loop == false) {
				// set animation to null.
				cAnim = nullptr;
				// Set back to idle sprite.
				sprite->setImage(idle.X, idle.Y);
			}
		}
	}
}

void GameObject::render() {
	sprite->render(rotation);
}

void GameObject::clean() {
	cAnim = nullptr;
	anims.clear();
	sprite->clean();
}

Vector2F GameObject::getPosition() {
	return this->position;
}

Vector2F GameObject::getSize() {
	return this->size;
}

void GameObject::setRotation(float theta) {
	if (!paused)
		this->rotation = theta;
}

float GameObject::getTheta() {
	return this->rotation;
}