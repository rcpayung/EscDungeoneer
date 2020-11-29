#include "Player.h"

Player::Player(std::string name, Vector2F p, float scale) : GameObject(name.c_str(),p,Vector2F(38,100)) {
	this->sprite = new Sprite(name.c_str(), "assets/playernew.bmp", p, Vector2F(38, 100), 1.0f);
	this->pushSprite(sprite);
	Animation anim;
	anim.duration = 120;
	anim.loop = true;
	anim.startFrame = Vector2F(0, 0);
	anim.numFrames = 2;
	this->addAnimation(0, anim);
}

void Player::setVelocityX(float vel) {
	this->VelX = vel;
}
void Player::setVelocityY(float vel) {
	this->VelY = vel;
}

void Player::update() {
	__super::update();
	Vector2F vel(VelX, VelY);
	this->setPosition(Vector2F(this->getPosition() + vel));
}
void Player::handleEvents(SDL_Event* e) {
	__super::handleEvents(e);
	switch (e->type) {
	case SDL_KEYDOWN:
		switch (e->key.keysym.sym) {
		case SDLK_w:
			setVelocityY(-5.0f);
			this->playAnimation(0, 0);
			break;
		case SDLK_a:
			setVelocityX(-5.0f);
			this->playAnimation(0, 0);
			break;
		case SDLK_s:
			setVelocityY(5.0f);
			this->playAnimation(0, 0);
			break;
		case SDLK_d:
			setVelocityX(5.0f);
			this->playAnimation(0, 0);
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e->key.keysym.sym) {
		case SDLK_w:
			setVelocityY(0.0f);
			this->cancelAnimation(0);
			this->playAnimation(0, 1);
			break;
		case SDLK_a:
			setVelocityX(0.0f);
			this->cancelAnimation(0);
			this->playAnimation(0, 1);
			break;
		case SDLK_s:
			setVelocityY(0.0f);
			this->cancelAnimation(0);
			this->playAnimation(0, 1);
			break;
		case SDLK_d:
			setVelocityX(0.0f);
			this->cancelAnimation(0);
			this->playAnimation(0, 1);
			break;
		}
		break;
	default:
		break;
	}
}