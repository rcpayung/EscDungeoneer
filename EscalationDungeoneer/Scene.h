#pragma once
#include "GameObject.h"

class Scene {
private:
	GameObject* player;
	std::vector<GameObject*> objects;
	SDL_Rect* camera;
public:


};

