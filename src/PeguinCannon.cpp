#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vec2.h"

#include <string>

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> PenguinBody) : Component(associated) {

    Sprite *PenguinCannonSprite = new Sprite("Recursos/img/cubngun.png", associated, 1, 1);
    associated.AddComponent(PenguinCannonSprite);

    pbody = PenguinBody;
    angle = 0;

}

void PenguinCannon::Start() {


}

void PenguinCannon::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();
    Vec2 mousePos(inputManager.GetMouseX(),inputManager.GetMouseY());

    if (pbody.lock() == nullptr) associated.RequestDelete();
    // associated.box.x = pbody.lock()->box.RectCenter().x
    // associated.box.y = pbody.lock()->box.RectCenter().y;
    associated.box.x = pbody.lock()->box.RectCenter().x - (associated.box.w/2);
    associated.box.y = pbody.lock()->box.RectCenter().y - (associated.box.h/2);
    float angle = mousePos.DegPntsVec2(associated.box.RectCenter());
    associated.angleDeg = angle;

}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(string type) {
    return true;
}

void PenguinCannon::Shoot() {

}