#include "Scene.h"

Scene::Scene(int id, std::string name, int openx, int openy, int SceneWidth, int SceneHeight, float scale) {
	this->id = id;
	this->name = name;
	player = new Player("Player",Vector2F(openx + GameManager::SCREENWIDTH / 2, openy + GameManager::SCREENHEIGHT / 2),1.0f);
	player->setPosition(Vector2F(GameManager::SCREENWIDTH / 2 - player->getSize().X / 2, GameManager::SCREENHEIGHT / 2 - player->getSize().Y / 2));
	GameObject* giantHornet = new GameObject("Giant Hornet", Vector2F(500, 500), Vector2F(128, 128));
	Sprite* sprite = new Sprite("Giant Hornet", "assets/giant_hornet.png", giantHornet->getPosition(), giantHornet->getSize(), 1.0f);

	giantHornet->pushSprite(sprite);
	this->objects.push_back(giantHornet);
	camera = {
		openx,
		openy,
		GameManager::SCREENWIDTH,
		GameManager::SCREENHEIGHT
	};

	this->SCENEWIDTH = SceneWidth;
	this->SCENEHEIGHT = SceneHeight;

	if (!loadScene()) {
		printf("Could Not Load Scene %s\n", name.c_str());
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
	printf("adding %d", int(obj->getID()));
	this->objects.push_back(obj);
}

void Scene::update() {
	camera.x = player->getPosition().X - GameManager::SCREENWIDTH / 2;
	camera.y = player->getPosition().Y - GameManager::SCREENHEIGHT / 2;

	player->update();
	for (GameObject* object : objects) {
		if (player->getPosition().X - 1000 < object->getPosition().X &&
			player->getPosition().X + 1000 > object->getPosition().X&&
			player->getPosition().Y - 1000 < object->getPosition().Y &&
			player->getPosition().Y + 1000 > object->getPosition().Y) {

			object->update();
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

void Scene::pollevents(SDL_Event* e) {
	player->handleEvents(e);
	switch (e->type) {
	case SDL_KEYDOWN:
		switch (e->key.keysym.sym) {
		case SDLK_b:

			break;
			default:
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