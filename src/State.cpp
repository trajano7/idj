#include "State.h"
#include "Face.h"
#include "TileMap.h"
#include "TileSet.h"

#include <cmath>
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

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
	objectArray.emplace_back(backGround);
	
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
	objectArray.emplace_back(scenery);

    quitRequested = false;
    music.Play(-1);

}

State::~State() {

    objectArray.clear();

}

void State::LoadAssets() {

    return;

}

void State::Update(float dt) {

	InputManager& inputManager = InputManager::GetInstance();

	Camera::Update(dt);

	//Check quit events
	if (inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	//Spawn a enemy if spacebar is pressed
	if (inputManager.KeyPress(SPACE_KEY)) {
		Vec2 objPos = Vec2( 200, 0 ).RotateVec2( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2( inputManager.GetMouseX(), inputManager.GetMouseY() );
		AddObject((int)objPos.x, (int)objPos.y);		
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

void State::AddObject(int mouseX, int mouseY) {

	GameObject* enemy;
	Sprite* sprite;
	Sound* sound;
	Face* face;

	enemy = new GameObject();
	sprite = new Sprite("Recursos/img/penguinface.png", *enemy);
	sound = new Sound(*enemy, "Recursos/audio/boom.wav");
	face = new Face(*enemy);

	//Adjust the coordenades to render the image center on it and sum the Camera position
	enemy->box.x = mouseX - sprite->GetWidth()/2 + ((int) round(Camera::pos.x));
	enemy->box.y = mouseY + sprite->GetHeight()/2 + ((int) round(Camera::pos.y));

	enemy->AddComponent(sprite);
	enemy->AddComponent(sound);
	enemy->AddComponent(face);

	objectArray.emplace_back(enemy);

}

bool State::QuitRequested() {

    return quitRequested;

}
