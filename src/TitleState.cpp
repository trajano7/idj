#include "TitleState.h"

#include "Game.h"
#include "Sprite.h"
#include "GameObject.h"
#include "InputManager.h"
#include "StageState.h"
#include "Camera.h"
#include "Text.h"

TitleState::TitleState() {

    //Title image GameObject creation
	GameObject* titleImgGO;
	Sprite* titleImg;

	titleImgGO = new GameObject();
	titleImg = new Sprite("Recursos/img/title.jpg", *titleImgGO, 1, -1,-1);
	titleImgGO->box.x = 0;
	titleImgGO->box.y = 0;
	titleImgGO->AddComponent(titleImg);
	AddObject(titleImgGO);

    //Title text GameObject creation
    GameObject* titleTextGO;
    Text* titleText;

    //Black color
    SDL_Color fontColor;
    fontColor.r = 0;
    fontColor.g = 0;
    fontColor.b = 0;
    fontColor.a = 0;

    titleTextGO = new GameObject();
    titleText = new Text(*titleTextGO,
                          "Recursos/font/Call me maybe.ttf",50,
                          Text::TextStyle::BLENDED,
                          "Pressione barra de espaco para continuar!",
                          fontColor,0.5);
    titleTextGO->box.x = 40;
    titleTextGO->box.y = 450;
    titleImgGO->AddComponent(titleText);
    AddObject(titleTextGO);

}

TitleState::~TitleState() {

}

void TitleState::Update(float dt) {

    InputManager& inputManager = InputManager::GetInstance();

    UpdateArray(dt);
    //Check quit events
	if (inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
    //Check if space was pressed to push the StageState
    if (inputManager.KeyPress(SPACE_KEY)) {
        Game::GetInstance().Push(new StageState());
    }

}

void TitleState::Render() {

    RenderArray();

}

void TitleState::LoadAssets() {

}

void TitleState::Start() {

	LoadAssets();
	StartArray();
	started = true;

}

void TitleState::Pause() {

}

void TitleState::Resume() {

    Camera::pos.x = 0;
    Camera::pos.y = 0;

}