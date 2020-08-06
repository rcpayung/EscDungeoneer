#pragma once
#include "Button.h"
#include "Text.h"

class Prompt : public UIComponent {
private:
	Text * message;
	Button * confirm, * close;
	bool confirmSet = false, cancelSet = false;
	SDL_Rect border;
public:
	Prompt(int x, int y, int w, int h, std::string alert);
	void setConfirm(void(*ptr) (std::string), std::string action);
	void setCancel(void(*ptr) (std::string), std::string action);
	void render();
	void update();
	void clean();
	void handleEvents(SDL_Event* e);
	void runConfirm();
};

