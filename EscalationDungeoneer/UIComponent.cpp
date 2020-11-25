#include "UIComponent.h"

UIComponent::UIComponent(int x, int y, int w, int h, float scale) {
	this->scale = scale;
	this->sprite = nullptr;
	this->dest = { x,y,w,h };
}

// Virtual function, mostly for inheritance
void UIComponent::render() {
	if (sprite != nullptr) {
		sprite->render();
	}
}
// Virtual function, mostly for inheritance
void UIComponent::update() {};
// Virtual function, mostly for inheritance
void UIComponent::setPosition(Vector2F f) {
	if (sprite != nullptr)
		sprite->setPosition(f.X, f.Y);
	else 
		dest = { f.X,f.Y,dest.w,dest.h };
}
// Virtual function, mostly for inheritance
void UIComponent::setPosition(int x, int y) {
	if (sprite != nullptr)
		sprite->setPosition(x,y);
	else {
		dest = {x,y,dest.w,dest.h};
	}
}
// Virtual function, mostly for inheritance
void UIComponent::clean() {
	if (sprite != nullptr) {
		sprite->clean();
	}
}

void UIComponent::setSize(int x, int y) {
	this->dest.w = x;
	this->dest.h = y;
}

// NON-VIRTUAL FUNCTIONS (NON-OVERRIDE)

float UIComponent::getScale() {
	return this->scale;
}
void UIComponent::setScale(float scale) {
	this->scale = scale;
	this->sprite->setScale(this->scale);
}
void UIComponent::setSprite(const char* asset) {
	this->sprite = new Sprite("UICOMPONENT",asset, Vector2F{ dest.x, dest.y }, Vector2F( dest.w, dest.h ), scale);
}
