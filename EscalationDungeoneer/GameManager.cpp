#include "GameManager.h"

bool GameManager::running = true;
bool GameManager::isPlaying = false;
bool GameManager::paused = false;
bool GameManager::devMode = false;

bool GameManager::setDev() {
	devMode = true;
	if (devMode) return true;
	return false;
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