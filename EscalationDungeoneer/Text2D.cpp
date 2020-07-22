#include "Text2D.h"

TTF_Font* Text2D::normal = nullptr;
TTF_Font* Text2D::bold = nullptr;
TTF_Font* Text2D::ibold = nullptr;
TTF_Font* Text2D::italic = nullptr;


/*
	* CONSTRUCTOR: Constructs the message into renderable pieces.
	* @ param message - message to be constructed. May contain things like fontweight
	* and font color supplied with attributes like so:
	* EXAMPLE: "<W = BOLD, C = GREEN>Hello World"
	* This Hello World would be bold and the color green. The color and font weight
	* will be set until another attribute is created. Even on different lines.
	* @ param fontsize - message will be constructed with this fontsize. this is essentially
	* pixel height.
	*
	*/
Text2D::Text2D(std::string message, int fontsize) {
	Text2D::normal = TTF_OpenFont("assets/fonts/Font/N.ttf", fontsize);
	Text2D::bold = TTF_OpenFont("assets/fonts/Font/B.ttf", fontsize);
	Text2D::italic = TTF_OpenFont("assets/fonts/Font/I.ttf", fontsize);
	Text2D::ibold = TTF_OpenFont("assets/fonts/Font/BI.ttf", fontsize);

	this->weight = Text2D::normal;
	this->currentColor = GameManager::BLACK;
	this->fontsize = fontsize;
	this->height = 0;
	this->width = 0;
	this->lineheight = 30;
	this->horiz = H_LEFT;
	this->verti = V_MIDDLE;

}

void Text2D::render() {

}

void Text2D::update() {

}

void Text2D::clean() {

}

void Text2D::alignVertical(int verti) {

}

void Text2D::alignHorizontal(int horiz) {
	
}

void Text2D::setPosition(int x, int y) {
	this->position = Vector2F(x, y);
}

Vector2F Text2D::getPosition() {
	return this->position;
}

int Text2D::getWidth() {
	return this->width;
}

bool Text2D::setWidth(int width) {
	if (this->getPosition().X + width > GameManager::SCREENWIDTH) {
		return false;
	}
	else {
		this->width = width;
	}
}

int Text2D::getLineHeight() {
	return this->lineheight;
}

bool Text2D::setLineHeight(int lineheight) {
	if (this->lineheight * lines.size() > height) {
		return false;
	}
	else {
		this->lineheight = lineheight;
		return true;
	}
}

int Text2D::getHeight() {
	return this->height;
}

void Text2D::setHeight(int height) {
	this->height = height;
}

SDL_Texture* Text2D::loadTexture(const char* message, SDL_Color color) {
	return nullptr;
}