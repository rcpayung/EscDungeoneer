/* @Author: Riley Payung
   @Name: SDL2 Escalation Dungeoneer
   @Version: 01-19-2020.0.0.3
   all includes are included in the Game.h file.
*/
#include "Game.h"

Game* game;

int main(int argc, char* argv[]) {
	game = new Game("Escalation Dungeoneer by Vestinius Games, LLC", 1536, 864, 0);
	
	const float FPS = 60.0;
	const int framedelay = 1000 / FPS;

	Uint32 framestart;
	float frameTime;
	while (game->isRunning()) {
		
		framestart = SDL_GetTicks();
		
		game->update();
		game->handleEvents();
		game->render();

		frameTime = SDL_GetTicks() - framestart;

		if (framedelay > frameTime)
			SDL_Delay(framedelay - frameTime);
	}

	game->cleanup();

	return 0;
}