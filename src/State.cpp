#include "State.h"
#include "TileMap.h"
#include "TileSet.h"

#include <cmath>
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.cpp"
#include "Collider.h"

State::State() : music("Recursos/audio/stageState.ogg") {

	started = false;

	//Background GameObject creation
	GameObject* backGround;
	Sprite* sprite;
	CameraFollower* cameraFollower;

	backGround = new GameObject();
	sprite = new Sprite("Recursos/img/ocean.jpg", *backGround, 1, 1,-1);
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

	AddObject(alienGO); 

	//Penguin player creation
	GameObject* penguinGO;
	PenguinBody* penguin;

	penguinGO = new GameObject();
	penguin = new PenguinBody(*penguinGO);
	penguinGO->AddComponent(penguin);
	penguinGO->box.x = 704;
	penguinGO->box.y = 640;

	AddObject(penguinGO);

	Camera::Follow(penguinGO);

    quitRequested = false;
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
	for (int i; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;

}

void State::Update(float dt) {

	InputManager& inputManager = InputManager::GetInstance();
	Collider *colliderA, *colliderB;

	Camera::Update(dt);;

	//Check quit events
	if (inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	//Call all GameObjects updates
	for (int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
	//Check if some collision occured between two GameObjects
	for (int i = 0; i < objectArray.size(); i++) {
		colliderA = static_cast<Collider*>(objectArray[i]->GetComponent("Collider"));
		if (colliderA == nullptr) continue;
		for (int j = i+1; j < objectArray.size(); j++) {
			colliderB = static_cast<Collider*>(objectArray[j]->GetComponent("Collider"));
			if (colliderB == nullptr) continue;
			bool collision = false;
			collision = Collision::IsColliding(colliderA->box,
								   					colliderB->box,
					               					objectArray[i]->angleDeg*(M_PI/180),
								   					objectArray[j]->angleDeg*(M_PI/180));
		    if (collision) {
				objectArray[i]->NotifyCollision(*objectArray[j]);
				objectArray[j]->NotifyCollision(*objectArray[i]);
			}
	
		}
	}
	//Check if some GameObject requested to be deleted
	for (int i = 0; i < objectArray.size(); i++) {
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

	for (int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == go) {
			weak_ptr<GameObject> weakPtr(objectArray[i]);
			return weakPtr;
		}
	}

	weak_ptr<GameObject> weakPtr;
	return weakPtr;

}

bool State::QuitRequested() {

    return quitRequested;

}
