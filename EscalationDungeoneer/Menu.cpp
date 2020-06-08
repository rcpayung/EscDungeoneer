#include "Menu.h"

Menu::Menu(SDL_Renderer* rd, int SCREENWIDTH, int SCREENHEIGHT, const char * title) {
	this->rd = rd;
	this->SCREENWIDTH = SCREENWIDTH;
	this->SCREENHEIGHT = SCREENHEIGHT;
	this->setTitle(title);
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
	SDL_SetRenderDrawColor(rd, 100, 100, 100, 100);
	SDL_RenderFillRect(rd, new SDL_Rect{ 0,0,SCREENWIDTH,SCREENHEIGHT });
	for (Text* c : labels) {
		c->render();
	}
	for (UIComponent* c : options) {
		c->render();
	}
}

void Menu::update() {
	for (UIComponent* c : options) {
		c->update();
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

