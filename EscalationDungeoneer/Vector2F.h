#pragma once
#include <string>
#include <stdio.h>
#include <iostream>

class Vector2F {
public:
	int X;
	int Y;
	Vector2F();
	Vector2F(const Vector2F& b) { X = b.X, Y = b.Y; };
	Vector2F(int x, int y);
	std::string to_string() const;

	bool operator==(Vector2F& y) {
		return (this->X == y.X && this->Y == y.Y) ? true : false;
	}
	Vector2F operator + (Vector2F& b) {
		return Vector2F(b.X + X, b.Y + Y);
	}
	Vector2F operator - (Vector2F& b) {
		return Vector2F(X - b.X, Y - b.Y);
	}
	Vector2F operator * (Vector2F& b) {
		return Vector2F(b.X * X, b.Y * Y);
	}
	Vector2F operator / (Vector2F& b) {
		return Vector2F(X / b.X, Y / b.Y);
	}
};

