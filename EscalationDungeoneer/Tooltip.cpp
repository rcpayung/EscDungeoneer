#include "Tooltip.h"

Tooltip::Tooltip(int fontsize, std::string tip, int fontWeight, SDL_Color fore, SDL_Color back, int x, int y) {
	this->fore = fore;
	this->back = back;
	this->fontsize = fontsize;
	this->fontweight = fontWeight;
	this->tip = tip;

	this->text = new Text(tip, fontsize, fontWeight, fore, Vector2F(x, y), Vector2F(static_cast<int>((fontsize / 1.5) * tip.length()), 30));
	this->dest = {x,y,text->getWidth() + 20,text->getHeight() + 10};
}

void Tooltip::setTip(std::string tip) {
	this->tip = tip;
	this->text->setText(tip);
	this->dest = { dest.x, dest.y,text->getWidth() + 20, text->getHeight() + 10 };
}

void Tooltip::setPosition(Vector2F p) {
	this->dest = { p.X, p.Y, dest.w, dest.h };
	this->border = { dest.x - 2, dest.y - 2,dest.w + 4,dest.h + 4 };
}

void Tooltip::setPosition(int x, int y) {
	this->dest = { x,y,dest.w,dest.h };
	this->border = { dest.x - 2, dest.y - 2,dest.w + 4,dest.h + 4 };
}

Vector2F Tooltip::getPosition() {
	return Vector2F(dest.x, dest.y);
}

void Tooltip::update() {
	this->text->setBounds(dest.x, dest.y, dest.w, dest.h);
	this->text->setCenter();
	this->text->setMiddle();
}

void Tooltip::render() {
	SDL_SetRenderDrawColor(GameManager::rd, back.r + 20, back.g + 20, back.b + 20, back.a);
	SDL_RenderFillRect(GameManager::rd, &border);
	SDL_SetRenderDrawColor(GameManager::rd, back.r, back.g, back.b, back.a);
	SDL_RenderFillRect(GameManager::rd, &dest);
	this->text->render();
	SDL_SetRenderDrawColor(GameManager::rd, 0, 0, 0, 255);
}

void Tooltip::clean() {
	text->clean();
}

int Tooltip::getWidth() {
	return dest.w;
}