#include "Menu.h"

Menu::Menu() {
	color = {0,0,0,0};
	screen = { 0,0,GameManager::SCREENWIDTH,GameManager::SCREENHEIGHT };
}

void Menu::setBackground(SDL_Color color) {
	this->color = color;
	this->drawBackground = true;
}

void Menu::addComponent(UIComponent* c) {
	this->options.push_back(c);
}

void Menu::addComponent(Text* t) {
	this->labels.push_back(t);
}

void Menu::setTitle(const char* title) {
	Text* t = new Text(title, 48, WBOLD, SDL_Color{200,200,200,255}, Vector2F(100, 50), Vector2F(500, 30));
	labels.push_back(t);
}

void Menu::render() {
	// Rendered backwards to properly show the tooltip, however, thinking about making this into a z-index renderer.
	if (this->drawBackground) {
		SDL_SetRenderDrawColor(GameManager::rd, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(GameManager::rd, &screen);
	}
	for (int i = static_cast<int>(labels.size() - 1); i >= 0; i--) {
		labels[i]->render();
	}
	for (int i = static_cast<int>(options.size() - 1); i >= 0; i--) {
		options[i]->render();
	}
}

void Menu::update() {
	for (int i = static_cast<int>(options.size()-1); i >= 0; i--) {
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
	switch (e->type) {
	case SDL_KEYDOWN:
		switch (e->key.keysym.sym) {
		case SDLK_ESCAPE:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
}

