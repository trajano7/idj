#include "Minion.h"

#include "Sprite.h"
#include "Vec2.h"
#include "Bullet.h"
#include "Game.h"

#include "cmath"

Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter) {

    Sprite *minionSprite = new Sprite("Recursos/img/minion.png", associated);
    associated.AddComponent(minionSprite);

    arc = arcOffsetDeg;

    Vec2 boxCenter = Vec2((*alienCenter.lock()).box.x + (*alienCenter.lock()).box.w/2
                         ,(*alienCenter.lock()).box.y + (*alienCenter.lock()).box.h/2);                 
    associated.box.x = (Vec2(200,0).RotateVec2(arc).x + boxCenter.x) - (associated.box.w)/2; 
    associated.box.y = (Vec2(200,0).RotateVec2(arc).y + boxCenter.y) - (associated.box.h)/2; 


}

void Minion::Update(float dt) {

    arc += 0.75*M_PI;

    Vec2 boxCenter = Vec2((*alienCenter.lock()).box.x + (*alienCenter.lock()).box.w/2
                         ,(*alienCenter.lock()).box.y + (*alienCenter.lock()).box.h/2);
    associated.box.x = (Vec2(200,0).RotateVec2(arc).x + boxCenter.x) - (associated.box.w)/2; 
    associated.box.y = (Vec2(200,0).RotateVec2(arc).y + boxCenter.y) - (associated.box.h)/2; 

}

void Minion::Render() {

}

bool Minion::Is(string type) {

    if("Minion" == type) {
        return true;
    }

    return false;    

}

void Minion::Shoot(Vec2 target) {

    GameObject *bulletGO = new GameObject();
    bulletGO->box.x = associated.box.x + (associated.box.w)/2;
    bulletGO->box.y = associated.box.y + (associated.box.h)/2;
    Bullet *bullet = new Bullet(*bulletGO,target.DegVec2(),100,10,200,"Recursos/img/minionbullet1.png");
    bulletGO->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(bulletGO);

}