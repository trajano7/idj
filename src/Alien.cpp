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

    GameObject *minionGO = new GameObject();
    Minion* minion = new Minion(*minionGO,Game::GetInstance().GetState().GetObjectPtr(&associated),90);
    minionGO->AddComponent(minion);
    minionArray.push_back(Game::GetInstance().GetState().AddObject(minionGO));
    minionGO = new GameObject();
    minion = new Minion(*minionGO,Game::GetInstance().GetState().GetObjectPtr(&associated),0);
    minionGO->AddComponent(minion);
    minionArray.push_back(Game::GetInstance().GetState().AddObject(minionGO));

}

void Alien::Update(float dt) {

    InputManager inputManager = InputManager::GetInstance();

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        SDL_Log("FIREEEEEEEEEE\n");
        Action action = Action(Action::SHOOT,(float) inputManager.GetMouseX() + Camera::pos.x, (float) inputManager.GetMouseY() + Camera::pos.y);
        taskQueue.push(action); 
    }
    else if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
        Action action = Action(Action::MOVE,(float) inputManager.GetMouseX() + Camera::pos.x, (float) inputManager.GetMouseY() + Camera::pos.y);
        taskQueue.push(action); 
    }

    if(!taskQueue.empty()) {
        Action action = taskQueue.front();
        //SDL_Log("%d %d\n", action.type, Action::SHOOT);
        if(action.type == Action::SHOOT) {
          Minion *minion = static_cast<Minion*>((*minionArray[0].lock()).GetComponent("Minion"));
          minion->Shoot(action.pos);
          taskQueue.pop();  
        }
        else if(action.type == Action::MOVE) {
          Vec2 dist;
          dist.x = action.pos.x - (associated.box.x + (associated.box.w)/2);
          dist.y = action.pos.y - (associated.box.y + (associated.box.h)/2);
          speed = (dist.UnitVec2()).MultScaVec2(5);
          if (dist.ModVec2() < speed.ModVec2()) {
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