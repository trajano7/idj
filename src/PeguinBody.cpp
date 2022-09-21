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
    hp = 30;
    player = this;

    invTimer = Timer();

}

PenguinBody::~PenguinBody() {

    player = nullptr;

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
        linearSpeed += 400*dt;
        if (linearSpeed > 500) linearSpeed = 400;
    }
    if (inputManager.IsKeyDown(SDLK_s)) {
        linearSpeed -= 400*dt;
        if (linearSpeed < -500) linearSpeed = -400;
    }
    //A and D to rotate the penguin anticlockwise or clockwise
    if (inputManager.IsKeyDown(SDLK_d)) {
        angle += 100*dt;
    }
    if (inputManager.IsKeyDown(SDLK_a)) {
        angle -= 100*dt;
    }

    //Calculates speed with the linearSpeed and angle
    speed.x = linearSpeed*cos(angle * (M_PI/180));
    speed.y = linearSpeed*sin(angle * (M_PI/180));
    associated.angleDeg = angle;
    associated.box.x += speed.x*dt;
    associated.box.y += speed.y*dt;  

    //Check if the penguin next position is out of the tileSet
    if (associated.box.x + associated.box.w >= 1480) associated.box.x = 1480 - associated.box.w;
    else if (associated.box.x < 0) associated.box.x = 0;
    
    if (associated.box.y + associated.box.h >= 1280) associated.box.y = 1280 - associated.box.h;
    else if (associated.box.y < 0) associated.box.y = 0;

    if (invTimer.Get() <= 0.8) {
        invTimer.Update(dt);
    }

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
    //Receive damage if its a bullet shot by alien and if its out of the invencible time
    if (bullet != nullptr && bullet->targetsPlayer && invTimer.Get() > 0.8) {
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
