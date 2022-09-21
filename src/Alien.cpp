#include "Alien.h"

#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Minion.h"
#include "Bullet.h"
#include "Collider.h"
#include "Sound.h"
#include "PenguinBody.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {

    Sprite *alienSprite = new Sprite("Recursos/img/alien.png", associated, 1, 1,-1);
    associated.AddComponent(alienSprite);
    Collider *collider = new Collider(associated,Vec2(1,1),Vec2(0,0));
    associated.AddComponent(collider);

    speed = Vec2(0,0);
    hp = 30;

    state = AlienState::RESTING;
    restTimer = Timer();
    destination = Vec2(0,0);

    alienCount++;
    //Draw a timeOffset
    timeOffset = ((float) (rand()%(100) + 33))/1000;
    // SDL_Log("offset = %f\n", timeOffset);

}

Alien::~Alien() {

    minionArray.clear();
    alienCount--;

}

void Alien::Start() {

    //Add 4 minions to the Alien
    GameObject *minionGO = new GameObject();
    Minion* minion = new Minion(*minionGO,Game::GetInstance().GetState().GetObjectPtr(&associated),0);
    for (int i = 0; i < 4; i++) {
        minionGO = new GameObject();
        minion = new Minion(*minionGO,Game::GetInstance().GetState().GetObjectPtr(&associated),i*90);
        minionGO->AddComponent(minion);
        minionArray.push_back(Game::GetInstance().GetState().AddObject(minionGO));
    }

}

void Alien::Update(float dt) {

    InputManager inputManager = InputManager::GetInstance();
    Vec2 dist;

    //Alien rotation speed around it origin
    associated.angleDeg -= 0.10*M_PI; 

    //Resting condition
    if (state == AlienState::RESTING) {
        restTimer.Update(timeOffset);
        //Move if the timer is greater than the limit and there is a player
        if (restTimer.Get() >= 0.66 && PenguinBody::player != nullptr) {
            destination = PenguinBody::player->GetPenguinPos();
            state = AlienState::MOVING;
        }
    }
    //Moving condition
    else if (state == AlienState::MOVING) {
        //Calculate the distance between the penguin and alien
        dist.x = destination.x - associated.box.RectCenter().x;
        dist.y = destination.y - associated.box.RectCenter().y;
        //Calculate the unit vector and multiplies by a scalar that defines how fast it move
        speed = (dist.UnitVec2()).MultScaVec2(350);
        if (dist.ModVec2() < speed.ModVec2()*dt || speed.ModVec2() == 0) { //If is close enough, if speed is 0, Penguin is stopped, so it only shoot
            //Put the Alien in the destination center
            associated.box.x = destination.x - (associated.box.w)/2;
            associated.box.y = destination.y - (associated.box.h)/2;
            speed = Vec2(0,0);
            int nextOne = 0;
            //Find the nearest minion to the penguin to shoot
            destination = PenguinBody::player->GetPenguinPos();
            for (int i = 1; i<minionArray.size(); i++) {
                if((*minionArray[i].lock()).box.RectCenter().DistVec2(destination) < 
                   (*minionArray[nextOne].lock()).box.RectCenter().DistVec2(destination)) {
                    nextOne = i;
                }
            }
            Minion *minion = static_cast<Minion*>((*minionArray[nextOne].lock()).GetComponent("Minion"));
            minion->Shoot(destination); 
            restTimer.Restart();
            state = AlienState::RESTING;  
        }
        else {
            associated.box.x += speed.x*dt;
            associated.box.y += speed.y*dt;
        }
    }

}

void Alien::Render() {

}
       
bool Alien::Is(string type) {

    if("Alien" == type) {
        return true;
    }

    return false;

}

void Alien::NotifyCollision(GameObject& other) {

    Bullet *bullet = static_cast<Bullet *>(other.GetComponent("Bullet"));
    //Check if other is a bullet and if it was shoot by the player
    if (bullet != nullptr && !bullet->targetsPlayer) {
        hp -= bullet->GetDamage();
        if(hp <= 0) { //Alien died
          //Creates a destruction animation with a sprite and sound in the same location of the Alien
          GameObject *explosionGO = new GameObject();
          Sprite *explosion = new Sprite("Recursos/img/aliendeath.png", *explosionGO, 4, 0.5,2); 
          explosionGO->box.x = associated.box.RectCenter().x - explosionGO->box.w/2;
          explosionGO->box.y = associated.box.RectCenter().y - explosionGO->box.h/2;
          Sound *explosionSound = new Sound(*explosionGO,"Recursos/audio/boom.wav");
          explosionSound->Play(1);
          explosionGO->AddComponent(explosion);
          explosionGO->AddComponent(explosionSound);
          Game::GetInstance().GetState().AddObject(explosionGO);
          //Request Alien GameObject destruction
          associated.RequestDelete();
        }
    }

}