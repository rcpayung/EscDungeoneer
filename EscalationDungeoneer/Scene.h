#pragma once
#include "GameObject.h"
#include "Player.h"

enum Tiles {
	GRA_DIR_UP_LT,
	GRA_DIR_UP_CE,
	GRA_DIR_UP_RT,
	GRA_DIR_PENN_UP,
	GRA_DIR_PENN_LE,
	GRA_DIR_PENN_RI,

};

class Scene {
private:
	int id;
	std::string name;
	std::vector<GameObject*> objects;
	SDL_Rect camera;
	bool isPaused = false;
	int** tileMap;
	int** logicMap;
	Player* player;
	int SCREENWIDTH, SCREENHEIGHT;
public:
	Scene(SDL_Renderer* rd, int id, std::string name, int openx, int openy, int SceneWidth, int SceneHeight, int SCREENWIDTH, int SCREENHEIGHT, float scale);
	bool loadScene();
	bool saveScene();

	void update(bool paused);
	void render();
	void clean();
	void handleCollisions(GameObject* a, GameObject* b);
	void pollevents(SDL_Event e);
};

