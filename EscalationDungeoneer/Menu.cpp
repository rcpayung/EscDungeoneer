#include "Menu.h"

Menu::Menu(SDL_Renderer* rd) {
	this->rd = rd;
}

void Menu::addComponent(UIComponent* c) {
	this->options.push_back(c);
}

void Menu::addComponent(Text* t) {
	this->labels.push_back(t);
}

void Menu::setTitle(const char* title) {
	Text* t = new Text(rd, title, 48, WBOLD, SDL_Color{200,200,200,255}, Vector2F(100, 50), Vector2F(500, 30));
	labels.push_back(t);
}

void Menu::render() {
	// Rendered backwards to properly show the tooltip, however, thinking about making this into a z-index renderer.
	for (int i = labels.size()-1; i >= 0; i--) {
		labels[i]->render();
	}
	for (int i = options.size()-1; i >= 0; i--) {
		options[i]->render();
	}
}

void Menu::update() {
	for (int i = options.size()-1; i >= 0; i--) {
		options[i]->update();
	}
}

void Menu::clean() {
	for (Text* c : labels) {
		c->clean();
	}
	for (UIComponent* c : options) {
		c->clean();
	}
}

void Menu::pollEvents(SDL_Event* e) {
	for (UIComponent* c : options) {
		c->handleEvents(e);
	}
}

