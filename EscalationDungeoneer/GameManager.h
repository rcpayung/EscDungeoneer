#pragma once
#include "Text.h"
#include <vector>
#include <string>

class GameManager {
public:
	static bool paused;
	static bool running;
	static bool editing;
	static bool devMode;
	static bool onMain;
	static bool isPlaying;
	static bool inSettings;
	static bool inInventory;
	static const char* versionNum;

	static std::vector<std::string> commands;

	static int SCREENWIDTH;
	static int SCREENHEIGHT;

	static SDL_Color WHITE;
	// Text Colors	  R   G   B
	static SDL_Color GREEN;
	static SDL_Color LGRAY;
	static SDL_Color L_BLU;
	static SDL_Color L_RED;
	static SDL_Color GRAY;
	static SDL_Color D_GRE;
	static SDL_Color DGRAY;
	static SDL_Color BLACK;
	static SDL_Color GOLD;
	static SDL_Color Gray20;
	
	static void setDev();
	static void Pause();
	static void setRunning();
	static void setPlaying();
	static void setEditing();
	static void pushCommand(std::string s);
};

