#include "GameManager.h"

bool GameManager::running = true;
bool GameManager::isPlaying = false;
bool GameManager::paused = false;
bool GameManager::devMode = false;

SDL_Color GameManager::WHITE = {255,255,255,255};
SDL_Color GameManager::GREEN{ 100, 200, 100, 255 };
SDL_Color GameManager::LGRAY{ 200, 200, 200, 255 };
SDL_Color GameManager::L_BLU{ 20, 90, 150, 255 };
SDL_Color GameManager::L_RED{ 150, 25, 25, 255 };
SDL_Color GameManager::GRAY{ 160, 160, 160, 255 };
SDL_Color GameManager::D_GRE{ 20, 50, 20, 255 };
SDL_Color GameManager::DGRAY{ 25, 25, 25, 255 };
SDL_Color GameManager::BLACK{ 0, 0, 0, 255 };
SDL_Color GameManager::GOLD{ 255, 215, 0, 255 };
SDL_Color GameManager::Gray20{ 45,45,45,255 };

int GameManager::SCREENWIDTH = 1080;
int GameManager::SCREENHEIGHT = 820;

void GameManager::setDev() {
	!GameManager::devMode ? GameManager::devMode = true : GameManager::devMode = false;
}

void GameManager::setRunning() {
	!GameManager::running ? GameManager::running = true : GameManager::running = false;
}

void GameManager::Pause() {
	!GameManager::paused ? GameManager::paused = true : GameManager::paused = false;
}

void GameManager::setPlaying() {
	!GameManager::isPlaying ? GameManager::isPlaying = true : GameManager::isPlaying = false;
}
/*
void GameManager::loadGame(const char* file) {

}
*/
