#include "State.h"
#include "TileMap.h"
#include "TileSet.h"

#include <cmath>
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"

State::State() : music("Recursos/audio/stageState.ogg") {

	//Background GameObject creation
	GameObject* backGround;
	Sprite* sprite;
	CameraFollower* cameraFollower;

	backGround = new GameObject();
	sprite = new Sprite("Recursos/img/ocean.jpg", *backGround);
	cameraFollower = new CameraFollower(*backGround);
	backGround->box.x = 0;
	backGround->box.y = 0;
	backGround->AddComponent(sprite);
	backGround->AddComponent(cameraFollower);
	//objectArray.emplace_back(backGround);
	AddObject(backGround);
	
	//TileMap GameObject creation
	GameObject* scenery;
	TileMap* tileMap;
	TileSet* tileSet;

	scenery = new GameObject();
	scenery->box.x = 0;
	scenery->box.y = 0;
	tileSet = new TileSet(64,64,"Recursos/img/tileset.png");
	tileMap = new TileMap(*scenery,"Recursos/map/tileMap.txt",tileSet);
	scenery->AddComponent(tileMap);
	//objectArray.emplace_back(scenery);
	AddObject(scenery);

	//Test Alien creation
	GameObject* alienGO;
	Alien* alien;

	alienGO = new GameObject();
	alien = new Alien(*alienGO,0);
	alienGO->AddComponent(alien);
	alienGO->box.x = 512 - (alienGO->box.w)/2;
	alienGO->box.y = 300 - (alienGO->box.h)/2;

	SDL_Log("%f %f", alienGO->box.x, alienGO->box.y);

	AddObject(alienGO);


    quitRequested = false;
	started = false;
    music.Play(-1);

}

State::~State() {

    objectArray.clear();

}

void State::LoadAssets() {

    return;

}

void State::Start() {

	LoadAssets();
	for (auto object : objectArray) {
		object->Start();
	}
	started = true;

}

void State::Update(float dt) {

	InputManager& inputManager = InputManager::GetInstance();

	Camera::Update(dt);

	//Check quit events
	if (inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
	for(int i = 0; i < objectArray.size(); i++) {
	    if (objectArray[i]->IsDead()) {
		   objectArray.erase(objectArray.begin()+i);	
		}
	}

}

void State::Render() {

	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}

    return;

}

weak_ptr<GameObject> State::AddObject(GameObject *go) {

	shared_ptr<GameObject> newObject(go);
	objectArray.push_back(newObject);
	if(started) newObject->Start();
	weak_ptr<GameObject> weakPtr(newObject);

	return weakPtr;

}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {

	for (auto object : objectArray) {
		if (object.get() == go) {
			weak_ptr<GameObject> weakPtr(object);
			return weakPtr;
		}
	}

	weak_ptr<GameObject> weakPtr;
	return weakPtr;

}

bool State::QuitRequested() {

    return quitRequested;

}
