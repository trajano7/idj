#include "StageState.h"
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
#include "GameData.h"
#include "Game.h"
#include "EndState.h"

#include "TitleState.h"

StageState::StageState() : State(), backgroundMusic("Recursos/audio/stageState.ogg") {

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
	AddObject(backGround);
	
	//TileMap GameObject creation
	GameObject* scenery;
	TileMap* tileMap;

	scenery = new GameObject();
	scenery->box.x = 0;
	scenery->box.y = 0;
	tileSet = new TileSet(64,64,"Recursos/img/tileset.png");
	tileMap = new TileMap(*scenery,"Recursos/map/tileMap.txt",tileSet);
	scenery->AddComponent(tileMap);
	AddObject(scenery);

	//Aliens creation
	for (int i = 0; i < 4; i++) {
		GameObject* alienGO;
		Alien* alien;

		alienGO = new GameObject();
		alien = new Alien(*alienGO,0);
		alienGO->AddComponent(alien);
		alienGO->box.x = rand()%1408; 
		alienGO->box.y = rand()%1280; 
		// SDL_Log("Posicoes alien: %f %f\n", alienGO->box.x, alienGO->box.y);
		AddObject(alienGO); 
	}


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

    backgroundMusic.Play(-1);

}

StageState::~StageState() {

	Camera::Unfollow();

}

void StageState::LoadAssets() {

}

void StageState::Start() {
	
	LoadAssets();
	StartArray();
	started = true;

}

void StageState::Pause() {

}

void StageState::Resume() {
	
}

void StageState::Update(float dt) {

	InputManager& inputManager = InputManager::GetInstance();
	Collider *colliderA, *colliderB;

	Camera::Update(dt);

	//Check quit events
	if (inputManager.QuitRequested()) {
		quitRequested = true;
	}
	//Check ESC key to return to the TitleState 
	if (inputManager.KeyPress(ESCAPE_KEY)) {
		popRequested = true;
	}

	//Call all GameObjects updates
	UpdateArray(dt);

	//Check if some collision occured between two GameObjects
	for (int i = 0; i < objectArray.size(); i++) {
		colliderA = static_cast<Collider*>(objectArray[i]->GetComponent("Collider"));
		if (colliderA == nullptr) continue; //If doesnt have a collider, continue
		for (int j = i+1; j < objectArray.size(); j++) {
			colliderB = static_cast<Collider*>(objectArray[j]->GetComponent("Collider"));
			if (colliderB == nullptr) continue;
			bool collision = false;
			//Check if some collision occurred
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

	//Check if some end game condition is met
	//Check if the player won
	if (Alien::alienCount == 0) {
		GameData::playerVictory = true;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}
	//Check if the player lost
	else if (PenguinBody::player == nullptr) {
		GameData::playerVictory = false;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}


}

void StageState::Render() {

	RenderArray();

}
