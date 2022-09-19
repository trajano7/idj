#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"

#include <cmath>
#include <string>

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {

    Sprite *PenguinBodySprite = new Sprite("Recursos/img/penguin.png", associated, 1, 1);
    associated.AddComponent(PenguinBodySprite);
    speed = Vec2(0,0);
    linearSpeed = 0;
    angle = 0;
    hp = 10;
    PenguinBody::player = this;

}

PenguinBody::~PenguinBody() {
    PenguinBody::player = nullptr;

}

void PenguinBody::Start() {

    GameObject* penguinCannonGO = new GameObject();
    PenguinCannon *penguinCannon = new PenguinCannon(*penguinCannonGO,Game::GetInstance().GetState().GetObjectPtr(&associated));
    penguinCannonGO->AddComponent(penguinCannon);
    // penguinCannonGO->box.x = associated.box.RectCenter().x - (penguinCannonGO->box.x)/2;
    // penguinCannonGO->box.y = associated.box.RectCenter().y - (penguinCannonGO->box.y)/2;
    pcannon = Game::GetInstance().GetState().AddObject(penguinCannonGO);

}

void PenguinBody::Update(float dt) {

    InputManager inputManager = InputManager::GetInstance();

    if (hp <= 0) {
        //(*pcannon.lock()).RequestDelete();
        associated.RequestDelete();
    }

    if (inputManager.IsKeyDown(SDLK_w)) {
        linearSpeed += 256*dt;
        if (linearSpeed > 500) linearSpeed = 500;
    }
    else if (inputManager.IsKeyDown(SDLK_s)) {
        linearSpeed -= 256*dt;
        if (linearSpeed < -500) linearSpeed = -500;
    }
    else {
        linearSpeed = 0;
    }
    if (inputManager.IsKeyDown(SDLK_d)) {
        angle += 2*M_PI;
    }
    else if (inputManager.IsKeyDown(SDLK_a)) {
        angle -= 2*M_PI;
    }

    speed.x = linearSpeed*cos(angle * (M_PI/180));
    speed.y = linearSpeed*sin(angle * (M_PI/180));
    associated.angleDeg = angle;
    associated.box.x += speed.x*dt;
    associated.box.y += speed.y*dt;  

}

void PenguinBody::Render() {

}

bool PenguinBody::Is(string type) {
    return true;
}
