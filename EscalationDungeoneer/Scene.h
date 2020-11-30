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
	int** tileMap; // two dimensional tilemap
	int** logicMap; // two dimensional logical map. All walls will be considered here.
	Player* player;
	int SCENEWIDTH, SCENEHEIGHT;
	float scale;
public:
	Scene(int id, std::string name, int openx, int openy, int SceneWidth, int SceneHeight, float scale);
	bool loadScene();
	bool saveScene(const char* path);
	void addObject(GameObject* obj);

	void setScale(float scale);

	void update();
	void render();
	void clean();
	void pollevents(SDL_Event* e);
};

