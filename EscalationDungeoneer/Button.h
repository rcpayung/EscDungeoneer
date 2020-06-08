#pragma once
#include "UIComponent.h"
#include "Text.h"

class Button : public UIComponent {
private:
	Text* label;
	SDL_Color f, b, fh, bh, sc;
	bool borderset, inside;
	int borderwidth;
	SDL_Rect border;
	// Action function
	void (*m_callback) ();
protected:

public:
	Button(SDL_Renderer* rd, int x, int y, int w, int h, const char* label);
	void setForeground(SDL_Color color);
	void setBackground(SDL_Color color);
	void setHover(SDL_Color fore, SDL_Color back);
	void setStroke(int width, SDL_Color borderColor);

	void render() override;
	void update() override;
	void clean() override;
	void handleEvents(SDL_Event* e) override;

	void setAction(void (ptr) ());

};

