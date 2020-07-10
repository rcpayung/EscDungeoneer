#pragma once
#include "Text.h"

class GameManager {
public:
	static bool paused;
	static bool running;
	static bool devMode;
	static bool isPlaying;

	static bool setDev();
	static void Pause();
	static void setRunning();
	static void setPlaying();
};

