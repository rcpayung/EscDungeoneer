#pragma once
#include "UIComponent.h"
#include "Text.h"

class Button : public UIComponent {
private:
	Text* label;
	Tooltip* tip;
	SDL_Color f, b, fh, bh, sc;
	bool borderset, inside, moving, tooltipvisible;
	int count;
	int borderwidth;
	std::string command;
	SDL_Rect border;
	// Action function
	void (*m_callback) ();
	void (*callback) (std::string);
	const char * labelstring;
protected:

public:
	Button(int x, int y, int w, int h, const char* label);
	void setForeground(SDL_Color color);
	void setBackground(SDL_Color color);
	void setHover(SDL_Color fore, SDL_Color back);
	void setStroke(int width, SDL_Color borderColor);

	void render() override;
	void update() override;
	void clean() override;
	void handleEvents(SDL_Event* e) override;

	void setAction(void (ptr) ()); 
	void setAction(void (*ptr) (std::string), std::string s);
	void sendCommand(std::string s);
	std::string getLabel();
	void setLabel(const char* label);
	void runCommand();
	void setPosition(int x, int y);
	void setPosition(Vector2F p);
	void setTooltip(std::string tip, int size, SDL_Color fore, SDL_Color back);

};

