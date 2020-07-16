#include "Text.h"

Text::Text(std::string message, short fontSize, int fontWeight,SDL_Color color, Vector2F p, Vector2F s) {
	if (message == "") {
		throw nullptr;
	}
	this->color = color;
	this->fontSize = fontSize;
	this->message = message;
	switch (fontWeight) {
	case WNORMAL:
		font = TTF_OpenFont("assets/fonts/Font/N.ttf", fontSize);
		break;
	case WBOLD:
		font = TTF_OpenFont("assets/fonts/Font/B.ttf", fontSize);
		break;
	case WITALIC:
		font = TTF_OpenFont("assets/fonts/Font/I.ttf", fontSize);
		break;
	case WBITALIC:
		font = TTF_OpenFont("assets/fonts/Font/BI.ttf", fontSize);
		break;
	default:
		font = TTF_OpenFont("assets/fonts/Font/N.ttf", fontSize);
		break;
	}
	if (!font) {
		printf("Error: %s\n", SDL_GetError());
	}

	tex = loadTexture(this->message, color);

	pos.x = p.X;
	pos.y = p.Y;
	this->setBounds(p.X, p.Y, s.X, s.Y);
}

void Text::render() {
	SDL_RenderCopy(GameManager::rd, tex, NULL, &pos);
}

void Text::setColor(SDL_Color color) {
	this->color = color;
	clean();
	tex = loadTexture(this->message,this->color);
}

void Text::setText(std::string message) {
	clean();
	this->message = message;
	tex = loadTexture(this->message, this->color);
}

SDL_Texture* Text::loadTexture(std::string message, SDL_Color color) {
	this->surf = TTF_RenderText_Blended(this->font, message.c_str(), color);
	if (message == "") {
		this->pos.w = 1;
		this->pos.h = 1;
	}
	else {
		this->pos.w = surf->w;
		this->pos.h = surf->h;
	}

	this->width = surf->w;
	this->height = surf->h;

	if (surf == NULL) {
		printf("Error in loading surface\n");
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::rd, surf);
	SDL_FreeSurface(this->surf);
	return texture;

}

void Text::clean() {
	SDL_DestroyTexture(tex);
}

void Text::setCenter() {
	pos.x = bounds.x + (bounds.w / 2) - (pos.w / 2);
}

void Text::setMiddle() {
	pos.y = bounds.y + (bounds.h / 2) - (pos.h / 2);
}

void Text::setBounds(int x, int y, int w, int h) {
	this->bounds = { x, y, w, h };
}

int Text::getWidth() {
	return this->width;
}

int Text::getHeight() {
	return this->height;
}