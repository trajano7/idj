#include "Camera.h"

#include "Game.h"
#include "InputManager.h"

Vec2 Camera::pos = Vec2(0,0);
Vec2 Camera::speed = Vec2(256,256); //Constant camera speed
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {

    focus = newFocus;

    return;

}

void Camera::Unfollow() {

    focus = nullptr;

    return;

}

void Camera::Update(float dt) {

    InputManager& inputManager = InputManager::GetInstance();

    //Following a focus
    if (focus != nullptr) {
       pos.x = focus->box.RectCenter().x - 512; //1024 width window 
       pos.y = focus->box.RectCenter().y - 300; //600 height window
    }
    //Without a focus
    else { 
       pos.x = pos.x + speed.x*dt*inputManager.IsKeyDown(RIGHT_ARROW_KEY); //False: 0, True: 1    
       pos.x = pos.x - speed.x*dt*inputManager.IsKeyDown(LEFT_ARROW_KEY);
       pos.y = pos.y + speed.y*dt*inputManager.IsKeyDown(DOWN_ARROW_KEY);
       pos.y = pos.y - speed.y*dt*inputManager.IsKeyDown(UP_ARROW_KEY);
    }


}