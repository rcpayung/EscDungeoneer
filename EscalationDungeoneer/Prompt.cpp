#include "Prompt.h"
Prompt::Prompt(int x, int y, int w, int h, std::string alert) : UIComponent(x, y, w, h, GameManager::scale) {
	message = new Text(alert, 12, WBOLD, GameManager::LGRAY, Vector2F(x,y+10), Vector2F(w, 30));
	message->setCenter();
	message->setMiddle();

	confirm = new Button(0, 0, 150, 30, "Confirm");
	close = new Button(0, 0, 150, 30, "Cancel");
	
	this->dest = { x, y, w, h };
	this->border = { x - 2, y - 2, w + 4, h + 4 };
	
	confirm->setBackground(GameManager::DGRAY);
	confirm->setForeground(GameManager::GOLD);
	confirm->setHover(GameManager::BLACK, GameManager::LGRAY);
	confirm->setStroke(2, GameManager::Gray20);

	close->setBackground(GameManager::DGRAY);
	close->setForeground(GameManager::GOLD);
	close->setHover(GameManager::BLACK, GameManager::LGRAY);
	close->setStroke(2, GameManager::Gray20);
}

void Prompt::setConfirm(void(*ptr) (std::string), std::string action) {
	this->confirm->setAction(ptr, action);
	this->confirmSet = true;
}

void Prompt::setCancel(void(*ptr) (std::string), std::string action) {
	this->close->setAction(ptr, action);
	this->cancelSet = true;
}

void Prompt::runConfirm() {
	if (confirmSet)
		confirm->runCommand();
}

void Prompt::render() {
	GameManager::setDrawColor(GameManager::Gray20);
	SDL_RenderFillRect(GameManager::rd, &border);
	GameManager::setDrawColor(GameManager::DGRAY);
	SDL_RenderFillRect(GameManager::rd, &dest);
	GameManager::setDrawColor(GameManager::BLACK);

	message->render();

	if (this->confirmSet)
		confirm->render();
	
	if (this->cancelSet)
		close->render();

	__super::render();
}

void Prompt::update() {
	confirm->update();
	close->update();

	if (confirmSet && !cancelSet)
		confirm->setPosition(dest.x + (dest.w / 2) - confirm->getSize().X / 2, dest.y + dest.h - 50);
	else if (!confirmSet && cancelSet)
		close->setPosition(dest.x + (dest.w / 2) - close->getSize().X / 2, dest.y + dest.h - 50);
	else {
		confirm->setPosition(dest.x + 20, dest.y + dest.h - 50);
		close->setPosition(dest.x + dest.w - 170, dest.y + dest.h - 50);
	}
}

void Prompt::clean() {
	message->clean();
	confirm->clean();
	close->clean();
}

void Prompt::handleEvents(SDL_Event* e) {
	confirm->handleEvents(e);
	close->handleEvents(e);
}