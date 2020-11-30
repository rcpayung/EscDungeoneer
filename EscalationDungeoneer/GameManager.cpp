#include "GameManager.h"

bool GameManager::running = true;
bool GameManager::isPlaying = false;
bool GameManager::paused = false;
bool GameManager::devMode = false;
bool GameManager::editing = false;
bool GameManager::onMain = true;
float GameManager::scale = 1.0f;
int GameManager::mx = 0;
int GameManager::my = 0;
bool GameManager::leftLock = false;

SDL_Renderer* GameManager::rd = nullptr;

bool GameManager::inSettings = false;
bool GameManager::inInventory = false;
const char* GameManager::versionNum = "PRE_ALPHA 0.1";
std::vector<std::string> GameManager::commands = std::vector<std::string>();
std::vector<std::string> GameManager::consoleLog = std::vector<std::string>();

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
 // RARITY COLORS
SDL_Color GameManager::COMMON{ 242,242,242,255 };
SDL_Color GameManager::UNCOMMON{ 185,208,159,255 };
SDL_Color GameManager::RARE{ 122,160,207,255 };
SDL_Color GameManager::VERYRARE{ 197,130,128,255 };
SDL_Color GameManager::LEGENDARY{ 159,142,179,255 };
SDL_Color GameManager::GODLY{ 235,195,50,255 };

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
	!GameManager::onMain ? GameManager::onMain = true : GameManager::onMain = false;
	if (GameManager::editing) {
		GameManager::editing = false;
	}
	!GameManager::isPlaying ? GameManager::isPlaying = true : GameManager::isPlaying = false;
}
/*
void GameManager::loadGame(const char* file) {

}
*/

void GameManager::setEditing() {
	!GameManager::editing ? GameManager::editing = true : GameManager::editing = false;
}

void GameManager::pushCommand(std::string s) {
	GameManager::commands.push_back(s);
	GameManager::consoleLog.push_back(s);
}

void GameManager::setDrawColor(SDL_Color color) {
	SDL_SetRenderDrawColor(GameManager::rd, color.r, color.g, color.b, color.a);
}

float GameManager::distance(Vector2F a, Vector2F b) {
	if (a == b) {
		return 0.0f;
	}
	else {
		return float(std::sqrt(std::pow(b.X - a.X, 2) + std::pow(b.Y - a.Y,2)));
	}
}