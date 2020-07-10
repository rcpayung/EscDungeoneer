#include "Scene.h"

Scene::Scene(SDL_Renderer* rd, int id, std::string name, int openx, int openy, int SceneWidth, int SceneHeight, int SCREENWIDTH, int SCREENHEIGHT, float scale) {
	this->id = id;
	this->name = name;
	player = new Player(rd,"Player",Vector2F(openx,openy),scale);
	player->setIdle(0, 0);
	player->addAnimation(10, 2, 0, 0, false);
	camera = {
		openx,
		openy,
		SCREENWIDTH,
		SCREENHEIGHT
	};

	this->SCREENWIDTH = SCREENWIDTH;
	this->SCREENHEIGHT = SCREENHEIGHT;
	this->SCENEWIDTH = SceneWidth;
	this->SCENEHEIGHT = SceneHeight;

	if (!loadScene()) {
		printf("Could Not Load Scene %s", name.c_str());
	}
}

bool Scene::loadScene() {
	tileMap = new int* [SCENEHEIGHT];
	logicMap = new int* [SCENEHEIGHT];
	for (int i = 0; i < SCENEHEIGHT; i++) {
		tileMap[i] = new int[SCENEWIDTH];
		logicMap[i] = new int[SCENEWIDTH];
	}

	std::string path = "scenes/";
	path.append(name);
	path.append(".dat");

	std::string line;
	std::vector<std::string> lines;
	std::ifstream tiles(path);
	if (tiles.is_open()) {
		while (std::getline(tiles, line)) {
			lines.push_back(line);
		}
	}

	return false;
}

bool Scene::saveScene(const char * path) {
	std::ofstream file(path);
	if (file.is_open()) {
		file.write(std::to_string(player->getPosition().X).c_str(), 5);
		file.write(std::to_string(player->getPosition().Y).c_str(), 5);
		for (GameObject* obj : objects) {
			file.write(std::to_string(obj->getID()).append(":").append(std::to_string(obj->getPosition().X)).append(":").append(std::to_string(obj->getPosition().Y)).c_str(), 50);
		}
		file.close();
		return true;
	}
	return false;
}

void Scene::addObject(GameObject* obj) {
	printf("adding %d", obj->getID());
	this->objects.push_back(obj);
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
			player->setVelocityY(-5.0f);
			player->playAnimation(0, false);
			break;
		case SDLK_a:
			player->setVelocityX(-5.0f);
			player->playAnimation(0, false);
			break;
		case SDLK_s:
			player->setVelocityY(5.0f);
			player->playAnimation(0, false);
			break;
		case SDLK_d:
			player->setVelocityX(5.0f);
			player->playAnimation(0, false);
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_w:
			player->setVelocityY(0.0f);
			break;
		case SDLK_a:
			player->setVelocityX(0.0f);
			break;
		case SDLK_s:
			player->setVelocityY(0.0f);
			break;
		case SDLK_d:
			player->setVelocityX(0.0f);
			break;
		}
		break;
	default:
		break;
	}
}

void Scene::setScale(float scale) {
	this->scale = scale;
}