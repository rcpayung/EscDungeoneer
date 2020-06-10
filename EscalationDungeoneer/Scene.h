#pragma once
#include "GameObject.h"
#include "Player.h"
#include <fstream>

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
	int SCREENWIDTH, SCREENHEIGHT, SCENEWIDTH, SCENEHEIGHT;
	float scale;
public:
	Scene(SDL_Renderer* rd, int id, std::string name, int openx, int openy, int SceneWidth, int SceneHeight, int SCREENWIDTH, int SCREENHEIGHT, float scale);
	bool loadScene();
	bool saveScene(const char* path);
	void addObject(GameObject* obj);

	void setScale(float scale);

	void update(bool paused);
	void render();
	void clean();
	void handleCollisions(GameObject* a, GameObject* b);
	void pollevents(SDL_Event e);
};

