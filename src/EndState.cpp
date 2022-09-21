#include "EndState.h"

#include "GameObject.h"
#include "Sprite.h"
#include "Text.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"

EndState::EndState() {

    //Black color
    SDL_Color fontColor;
    fontColor.r = 0;
    fontColor.g = 0;
    fontColor.b = 0;
    fontColor.a = 0;

    //Create and add end background image GameObject
    GameObject* endImgGO;
    Sprite* endImg;

    endImgGO = new GameObject();

    //Choose between winning or loss image and music
    if (GameData::playerVictory) {
        endImg = new Sprite("Recursos/img/win.jpg", *endImgGO, 1, -1,-1);
        backgroundMusic = Music("Recursos/audio/endStateWin.ogg");
    }
    else {
        endImg = new Sprite("Recursos/img/lose.jpg", *endImgGO, 1, -1,-1);
        backgroundMusic = Music("Recursos/audio/endStateLose.ogg");
    }
    endImgGO->box.x = 0;
	endImgGO->box.y = 0;
    endImgGO->AddComponent(endImg);
    AddObject(endImgGO);

    //Create and add end text GameObject
    GameObject* endTextGO;
    Text* endText;

    endTextGO = new GameObject();
    endText = new Text(*endTextGO,
                          "Recursos/font/Call me maybe.ttf",30,
                          Text::TextStyle::BLENDED,
                          "Pressione barra de espaco para jogar novamente ou ESC para sair do jogo!",
                          fontColor,1);
    endTextGO->box.x = 20;
    endTextGO->box.y = 450;
    endTextGO->AddComponent(endText);
    AddObject(endTextGO);

}

EndState::~EndState() {

}

void EndState::LoadAssets() {

}

void EndState::Render() {

    RenderArray();

}

void EndState::Update(float dt) {

    InputManager& inputManager = InputManager::GetInstance();

    UpdateArray(dt);
    //Check quit conditions
    if (inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
    //Check play again codition, go back to first state (TitleState)
    else if (inputManager.KeyPress(SPACE_KEY)) {
        popRequested = true;
    }

}

void EndState::Start() {

    backgroundMusic.Play(-1);
	LoadAssets();
	StartArray();
	started = true;

}

void EndState::Pause() {

}

void EndState::Resume() {

    Camera::pos.x = 0;
    Camera::pos.y = 0;

}

