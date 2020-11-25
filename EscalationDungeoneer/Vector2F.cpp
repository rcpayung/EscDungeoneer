#include "Vector2F.h"

Vector2F::Vector2F() {
	this->X = 0;
	this->Y = 0;
}

Vector2F::Vector2F(int x, int y) {
	this->X = x;
	this->Y = y;
}

std::string Vector2F::to_string() const {
	return "(X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ")";
}