#include "Player.h"

Player::Player(std::string name, Vector2F p, float scale) : GameObject(name, Vector2F(p.X, p.Y), Sizer{ 64, 128 }, "assets/player.png") {

}

void Player::setVelocityX(float vel) {
	this->VelX = vel;
}
void Player::setVelocityY(float vel) {
	this->VelY = vel;
}
/*
void Player::setMaxHP(int HP);
void Player::setHP(int HP);

void Player::setMaxMP(int MP);
void Player::setMP(int MP);

void Player::levelUp();

void Player::setSpeed(float speed);

void Player::setATT(int amount);
void Player::setDEF(int amount);
void Player::setVIT(int amount);
void Player::setWIS(int amount);
void Player::setDEX(int amount);
*/
void Player::update() {
	__super::update();
	this->setPosition(this->getPosition().X + VelX, this->getPosition().Y + VelY);
}