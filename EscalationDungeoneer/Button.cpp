#include "Button.h"

Button::Button(SDL_Renderer* rd, int x, int y, int w, int h, const char* label) : UIComponent(rd, x, y, w, h, 1.0f) {
	// Default color black.
	f = { 0,0,0,255 };
	b = { 255,255,255,255 };
	fh = f;
	bh = b;
	sc = { 255,255,255,0 };

	borderset = false;
	this->label = new Text(rd, label, 15, WNORMAL, f, Vector2F(x, y), Vector2F(w, h));
	inside = false;
	this->label->setBounds(x, y, w, h);
	this->label->setCenter();
	this->label->setMiddle();
	this->m_callback = nullptr;
}

void Button::setForeground(SDL_Color color) {
	this->f = color;
	this->label->setColor(f);
}

void Button::setBackground(SDL_Color color) {
	this->b = color;
}

void Button::setHover(SDL_Color fore, SDL_Color back) {
	this->fh = fore;
	this->bh = back;
}

void Button::setStroke(int width, SDL_Color borderColor) {
	this->borderset = true;
	this->borderwidth = width;
	this->sc = borderColor;
}

// Overridden

void Button::render() {
	__super::render();
	if (inside) {
		// Hover
		SDL_SetRenderDrawColor(rd, sc.r, sc.g, sc.b, sc.a);
		SDL_RenderFillRect(rd, &border);
		SDL_SetRenderDrawColor(rd, bh.r, bh.g, bh.b, bh.a);
		SDL_RenderFillRect(rd, &dest);
		label->setColor(fh);
		label->render();
	} else {
		// No Hover
		SDL_SetRenderDrawColor(rd, sc.r, sc.g, sc.b, sc.a);
		SDL_RenderFillRect(rd, &border);
		SDL_SetRenderDrawColor(rd, b.r, b.g, b.b, b.a);
		SDL_RenderFillRect(rd, &dest);
		label->setColor(f);
		label->render();
	}
	SDL_SetRenderDrawColor(rd, 0, 0, 0, 255);
}
// Virtual function, mostly for inheritance
void Button::setAction(void (ptr) ()) {
	m_callback = ptr;
}

void Button::update() {
	if (borderset) {
		border = { dest.x - borderwidth, dest.y - borderwidth, dest.w + 2 * borderwidth, dest.h + 2 * borderwidth };
	}
}

void Button::clean() {
	__super::clean();
	label->clean();
}

void Button::handleEvents(SDL_Event* e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch (e->type) {
	case SDL_MOUSEMOTION:
		
		if (x > this->getPosition().X&& x < (this->getPosition().X + this->getSize().X) 
			&& y > this->getPosition().Y&& y < (this->getPosition().Y + this->getSize().Y)) {
			inside = true;
		}
		else {
			inside = false;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (e->button.button) {
		case SDL_BUTTON_LEFT:
			if (x > this->getPosition().X&& x < (this->getPosition().X + this->getSize().X)
				&& y > this->getPosition().Y&& y < (this->getPosition().Y + this->getSize().Y)) {
				if (m_callback != nullptr) m_callback();
			}
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}