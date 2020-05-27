#include "Player.h"

Player::Player(SDL_Renderer* rd, std::string name, Vector2F p, float scale) : GameObject(rd, name, p.X, p.Y, 64, 128, scale, "assets/player.png") {

}