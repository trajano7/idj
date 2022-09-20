#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"

#include <cmath>
#include <string>

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {

    Sprite *PenguinBodySprite = new Sprite("Recursos/img/penguin.png", associated, 1, 1,-1);
    associated.AddComponent(PenguinBodySprite);
    Collider *collider = new Collider(associated,Vec2(1,1),Vec2(0,0));
    associated.AddComponent(collider);

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

    //Creates a PenguinCannon
    GameObject* penguinCannonGO = new GameObject();
    PenguinCannon *penguinCannon = new PenguinCannon(*penguinCannonGO,Game::GetInstance().GetState().GetObjectPtr(&associated));
    penguinCannonGO->AddComponent(penguinCannon);
    pcannon = Game::GetInstance().GetState().AddObject(penguinCannonGO);

}

void PenguinBody::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();

    //W and S to move foward or backward
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
    //A and D to rotate the penguin anticlockwise or clockwise
    if (inputManager.IsKeyDown(SDLK_d)) {
        angle += 2*M_PI;
    }
    else if (inputManager.IsKeyDown(SDLK_a)) {
        angle -= 2*M_PI;
    }

    //Calculates speed with the linearSpeed and angle
    speed.x = linearSpeed*cos(angle * (M_PI/180));
    speed.y = linearSpeed*sin(angle * (M_PI/180));
    associated.angleDeg = angle;
    associated.box.x += speed.x*dt;
    associated.box.y += speed.y*dt;  

}

void PenguinBody::Render() {

}

bool PenguinBody::Is(string type) {

    if("PenguinBody" == type) {
        return true;
    }

    return false;

}

void PenguinBody::NotifyCollision(GameObject& other) {

    Bullet *bullet = static_cast<Bullet *>(other.GetComponent("Bullet"));
    if (bullet != nullptr && bullet->targetsPlayer) {
        hp -= bullet->GetDamage();
        if (hp <= 0) {
            Camera::Unfollow();
            GameObject *explosionGO = new GameObject();
            //Creates a explosion animation with a sprite and sound in the same location of the Penguin
            Sprite *explosion = new Sprite("Recursos/img/penguindeath.png", *explosionGO, 5, 0.4,2); 
            explosionGO->box.x = associated.box.RectCenter().x - explosionGO->box.w/2;
            explosionGO->box.y = associated.box.RectCenter().y - explosionGO->box.h/2;
            Sound *explosionSound = new Sound(*explosionGO,"Recursos/audio/boom.wav");
            explosionSound->Play(1);
            explosionGO->AddComponent(explosion);
            explosionGO->AddComponent(explosionSound);
            Game::GetInstance().GetState().AddObject(explosionGO);  
            //Request PenguinBody and PenguinCannon GameObjects destructions
            (*pcannon.lock()).RequestDelete();
            associated.RequestDelete();
        }
    }

}

Vec2 PenguinBody::GetPenguinPos() {

    return associated.box.RectCenter();

}
