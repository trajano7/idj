#include "Alien.h"

#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Minion.h"
#include "Bullet.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {

    Sprite *alienSprite = new Sprite("Recursos/img/alien.png", associated);
    associated.AddComponent(alienSprite);

    speed = Vec2(0,0);
    hp = 30;

}

Alien::~Alien() {

    minionArray.clear();

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

    //Alien rotation speed around it origin
    associated.angleDeg -= 0.10*M_PI; 

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) { //Shoot action
        //SDL_Log("FIREEEEEEEEEE\n");
        Action action = Action(Action::SHOOT,(float) inputManager.GetMouseX() + Camera::pos.x, (float) inputManager.GetMouseY() + Camera::pos.y);
        taskQueue.push(action); 
    }
    else if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) { //Move action
        Action action = Action(Action::MOVE,(float) inputManager.GetMouseX() + Camera::pos.x, (float) inputManager.GetMouseY() + Camera::pos.y);
        taskQueue.push(action); 
    }

    if(!taskQueue.empty()) {
        Action action = taskQueue.front();
        if(action.type == Action::SHOOT) {
          int nextOne = 0;
          //Find the nearest minion to the mouse click position to shoot
          for (int i = 1; i<minionArray.size();i++) {
            if((*minionArray[i].lock()).box.RectCenter().DistVec2(action.pos) < 
               (*minionArray[nextOne].lock()).box.RectCenter().DistVec2(action.pos)) {
                nextOne = i;
               }
          }
          Minion *minion = static_cast<Minion*>((*minionArray[nextOne].lock()).GetComponent("Minion"));
          minion->Shoot(action.pos);
          taskQueue.pop();  
        }
        else if(action.type == Action::MOVE) {
          Vec2 dist;
          //Calculate the distance vector
          dist.x = action.pos.x - associated.box.RectCenter().x;
          dist.y = action.pos.y - associated.box.RectCenter().y;
          //Calculate the unit vector and multiplies by a scalar that defines how fast it move
          speed = (dist.UnitVec2()).MultScaVec2(5);
          //If the current distance is smaller that the speed it just move the Alien to the final point
          if (dist.ModVec2() < speed.ModVec2()) {
            //Put the Alien center in the click position
            associated.box.x = action.pos.x - (associated.box.w)/2;
            associated.box.y = action.pos.y - (associated.box.w)/2;
            speed = Vec2(0,0);
            taskQueue.pop();
          }
          else {
            associated.box.x += speed.x;
            associated.box.y += speed.y;
          }
        }    
    }

    if(hp <= 0) associated.RequestDelete();

}

void Alien::Render() {

}
       
bool Alien::Is(string type) {

    if("Alien" == type) {
        return true;
    }

    return false;

}

Alien::Action::Action(ActionType type, float x, float y) {

    this->type = type;
    pos.x = x;
    pos.y = y;

}