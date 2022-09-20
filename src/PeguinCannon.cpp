#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Bullet.h"
#include "Game.h"
#include "Camera.h"
#include "Collider.h"

#include <cmath>
#include <string>

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> PenguinBody) : Component(associated) {

    Sprite *PenguinCannonSprite = new Sprite("Recursos/img/cubngun.png", associated, 1, 1,-1);
    associated.AddComponent(PenguinCannonSprite);
    Collider *collider = new Collider(associated,Vec2(1,1),Vec2(0,0));
    associated.AddComponent(collider);

    pbody = PenguinBody;
    angle = 0;

    cooldown = Timer();

}

void PenguinCannon::Start() {


}

void PenguinCannon::Update(float dt) {

    InputManager inputManager = InputManager::GetInstance();
    Vec2 mousePos(inputManager.GetMouseX() + Camera::pos.x,inputManager.GetMouseY() + Camera::pos.y);

    if (pbody.lock() == nullptr) associated.RequestDelete();
 
    //Rotates the PenguinCannon accordingly to mouse position
    associated.box.x = pbody.lock()->box.RectCenter().x - (associated.box.w/2);
    associated.box.y = pbody.lock()->box.RectCenter().y - (associated.box.h/2);
    angle = mousePos.DegPntsVec2(associated.box.RectCenter());
    associated.angleDeg = angle;

    //Shoot if the left mouse button was clicked and the cooldown time passed
    cooldown.Update(dt);
    if (inputManager.MousePress(LEFT_MOUSE_BUTTON) && cooldown.Get() >= 0.66) {
        cooldown.Restart();
        Shoot();
    }

}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(string type) {

    if("PenguinCannon" == type) {
        return true;
    }

    return false;

}

void PenguinCannon::Shoot() {

    GameObject *bulletGO = new GameObject();
    Bullet *bullet = new Bullet(*bulletGO,angle,256,10,400,
                                "Recursos/img/penguinbullet.png",4,0.33,false);

    float Cos = cos(angle * (M_PI/180));
    float Sin = sin(angle * (M_PI/180));

    //Bullet spawn in the cannon end and move accordingly to angle calculated in Update
    bulletGO->box.x = ((associated.box.RectCenter()).x + (associated.box.w/2)*Cos) - bulletGO->box.w/2;    
    bulletGO->box.y = ((associated.box.RectCenter()).y + (associated.box.w/2)*Sin) - bulletGO->box.h/2; 
    bulletGO->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(bulletGO);

}

void PenguinCannon::NotifyCollision(GameObject& other) {

    //pbody.lock()->NotifyCollision(other);

}