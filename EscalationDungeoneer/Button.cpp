#include "Button.h"
#include "GameManager.h"

Button::Button(int x, int y, int w, int h, const char* label) : UIComponent(x, y, w, h, 1.0f) {
	// Default color black.
	this->f = { 0,0,0,255 };
	this->b = { 255,255,255,255 };
	this->fh = f;
	this->bh = b;
	this->sc = { 255,255,255,0 };

	this->borderset = false;
	this->inside = false;
	this->moving = false;
	this->borderwidth = 0;
	if (label != nullptr) {
		this->label = new Text(label, 15, WNORMAL, f, Vector2F(x, y), Vector2F(w, h));
		this->label->setBounds(x, y, w, h);
		this->label->setCenter();
		this->label->setMiddle();
	}
	this->m_callback = nullptr;
	this->count = 0;
	this->border = {};
	this->tip = nullptr;
	this->tooltipvisible = false;
	this->labelstring = label;
}

void Button::setLabel(const char* label) {
	this->label->setText(label);
}

std::string Button::getLabel() {
	return this->labelstring;
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
	SDL_SetRenderDrawColor(GameManager::rd, sc.r, sc.g, sc.b, sc.a);
	SDL_RenderFillRect(GameManager::rd, &border);
	if (inside) {
		// Hover
		SDL_SetRenderDrawColor(GameManager::rd, bh.r, bh.g, bh.b, bh.a);
		SDL_RenderFillRect(GameManager::rd, &dest);
		this->label->setColor(fh);
		this->label->render();
		if (this->tip != nullptr && tooltipvisible) {
			this->tip->render();
		}
	} else {
		// No Hover
		
		SDL_SetRenderDrawColor(GameManager::rd, b.r, b.g, b.b, b.a);
		SDL_RenderFillRect(GameManager::rd, &dest);
		this->label->setColor(f);
		this->label->render();
	}
	SDL_SetRenderDrawColor(GameManager::rd, 0, 0, 0, 255);
}
// Virtual function, mostly for inheritance
void Button::setAction(void (ptr) ()) {
	m_callback = ptr;
}

void Button::setAction(void (*ptr) (std::string),std::string s) {
	this->callback = ptr;
	this->command = s;
}

void Button::sendCommand(std::string s) {
	GameManager::pushCommand(s);
}

void Button::update() {
	if (moving) {
		this->setPosition(GameManager::mx, GameManager::my);
	}
	if (borderset) {
		border = { dest.x - borderwidth, dest.y - borderwidth, dest.w + 2 * borderwidth, dest.h + 2 * borderwidth };
	}
	if (!inside) {
		this->count = 0;
		this->tooltipvisible = false;
	}
	else {
		this->count++;
		if (count > 30) {
			this->tooltipvisible = true;
			if (tip != nullptr) {
				if (GameManager::mx + 10 + tip->getWidth() > GameManager::SCREENWIDTH) {
					if (GameManager::my + 50 > GameManager::SCREENHEIGHT) {
						this->tip->setPosition(GameManager::SCREENWIDTH - tip->getWidth() - 2, GameManager::my - 40);
					}
					else {
						this->tip->setPosition(GameManager::SCREENWIDTH - tip->getWidth() - 2, GameManager::my + 20);
					}
				}
				else if (GameManager::my + 60 > GameManager::SCREENHEIGHT)
					this->tip->setPosition(GameManager::mx + 10, GameManager::my - 40);
				else
					this->tip->setPosition(GameManager::mx + 10, GameManager::my + 20);
				this->tip->update();
			}
		}
	}
}

void Button::clean() {
	__super::clean();
	label->clean();
	if (tip != nullptr)
		tip->clean();
}

void Button::runCommand() {
	if (this->callback != nullptr) {
		callback(command);
	}
}

void Button::handleEvents(SDL_Event* e) {
	switch (e->type) {
	case SDL_MOUSEMOTION:
		// If within the bounds of the button
		if (GameManager::mx > this->getPosition().X && GameManager::mx < (this->getPosition().X + this->getSize().X)
			&& GameManager::my > this->getPosition().Y && GameManager::my < (this->getPosition().Y + this->getSize().Y)) {
			this->inside = true;
		}
		else {
			this->inside = false;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (e->button.button) {
		case SDL_BUTTON_LEFT:
			if (this->inside) {
				if (m_callback != nullptr) {
					m_callback();
				}
				else
					runCommand();
				this->inside = false;
			}
			break;
		case SDL_BUTTON_RIGHT:
			this->moving = false;
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (e->button.button) {
		case SDL_BUTTON_RIGHT:
			if (this->inside && GameManager::devMode) this->moving = true;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Button::setPosition(int x, int y) {
	__super::setPosition(x, y);
	this->label->setBounds(this->getPosition().X, this->getPosition().Y, this->getSize().X,this->getSize().Y);
	this->label->setCenter();
	this->label->setMiddle();
	if (tip != nullptr)
		this->tip->setPosition(x, y+20);
}


void Button::setPosition(Vector2F p) {
	__super::setPosition(p);
	this->label->setBounds(p.X,p.Y, this->getSize().X, this->getSize().Y);
	this->label->setCenter();
	this->label->setMiddle();
	if (tip != nullptr)
		this->tip->setPosition(p.X, p.Y + 20);
}

void Button::setTooltip(std::string tip, int size, SDL_Color fore, SDL_Color back) {
	this->tip = new Tooltip(size, tip, WNORMAL, fore, back, GameManager::mx, GameManager::my+50);
}