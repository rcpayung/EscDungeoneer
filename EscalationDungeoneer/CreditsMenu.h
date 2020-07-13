#pragma once
#include "Menu.h"
class CreditsMenu : public Menu {
private:
	std::vector<Text*> paras;
	Button* back;
	Sprite* vestinius;
	int last = 0;
public:
	CreditsMenu();
	void render();
	void clean();
	void update();
	void addText(std::string message, int size);
	void addSpacing(int amount);
};

