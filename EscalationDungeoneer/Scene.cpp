#include "Scene.h"

Scene::Scene(SDL_Renderer* rd, int id, std::string name, int openx, int openy, int SceneWidth, int SceneHeight, int SCREENWIDTH, int SCREENHEIGHT, float scale) {
	this->id = id;
	this->name = name;
	player = new Player(rd,"Player",Vector2F(openx,openy),scale);
	camera = {
		openx,
		openy,
		1080,
		720
	};

	this->SCREENWIDTH = SCREENWIDTH;
	this->SCREENHEIGHT = SCREENHEIGHT;
	
	tileMap = new int*[SceneHeight];
	logicMap = new int*[SceneHeight];
	for (unsigned int i = 0; i < SceneHeight; i++) {
		tileMap[i] = new int[SceneWidth];
		logicMap[i] = new int[SceneWidth];
	}
	
}


void Scene::update(bool paused) {
	camera.x = player->getPosition().X - SCREENWIDTH / 2;
	camera.y = player->getPosition().Y - SCREENHEIGHT / 2;

	player->update(paused);
	for (GameObject* object : objects) {
		if (player->getPosition().X - 1000 < object->getPosition().X &&
			player->getPosition().X + 1000 > object->getPosition().X&&
			player->getPosition().Y - 1000 < object->getPosition().Y &&
			player->getPosition().Y + 1000 > object->getPosition().Y) {

			object->update(paused);
		}
	}
}


void Scene::render() {
	// Render tiles here.
	player->render();
	for (GameObject* object : objects) {
		object->render();
	}
}



void Scene::clean() {
	player->clean();
	for (GameObject* object : objects) {
		object->clean();
	}
}

void Scene::pollevents(SDL_Event e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_w:
			player->setPosition(player->getPosition().X + 50, player->getPosition().Y + 50);
			break;
		case SDLK_a:
			
			break;
		case SDLK_s:
			
			break;
		case SDLK_d:
			
			break;
		}
		break;
	default:
		break;
	}
}