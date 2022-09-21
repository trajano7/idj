#include "Minion.h"

#include "Sprite.h"
#include "Vec2.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"

#include "cmath"

Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter) {

    Sprite *minionSprite = new Sprite("Recursos/img/minion.png", associated, 1, 1,-1);
    //Calculate a random scala to each Minion created
    double scale = (((double) rand() / (double) RAND_MAX) * 0.5) + 1;
    minionSprite->SetScaleX(scale,scale);
    //SDL_Log("scala = %lf\n", scale);
    associated.AddComponent(minionSprite);
    Collider *collider = new Collider(associated,Vec2(1,1),Vec2(0,0));
    associated.AddComponent(collider);

    //Initial arc
    arc = arcOffsetDeg;

    //Calculate the initial Minion position
    Vec2 boxCenter = (*alienCenter.lock()).box.RectCenter();                
    associated.box.x = (Vec2(200,0).RotateVec2(arc).x + boxCenter.x) - (associated.box.w)/2; 
    associated.box.y = (Vec2(200,0).RotateVec2(arc).y + boxCenter.y) - (associated.box.h)/2; 


}

void Minion::Update(float dt) {

    //Check if the Alien was destroyed
    if (!alienCenter.lock()) {
        GameObject *explosionGO = new GameObject();
        //Creates a destruction animation with a sprite and sound in the same location of the Minion
        Sprite *explosion = new Sprite("Recursos/img/miniondeath.png", *explosionGO, 4, 0.5,2); 
        explosionGO->box.x = associated.box.RectCenter().x - explosionGO->box.w/2;
        explosionGO->box.y = associated.box.RectCenter().y - explosionGO->box.h/2;
        explosionGO->AddComponent(explosion);
        Vec2 scale = (static_cast<Sprite *>(associated.GetComponent("Sprite")))->GetScale();
        explosion->SetScaleX(scale.x,scale.y);
        Game::GetInstance().GetState().AddObject(explosionGO);
        //Request Minion GameObject destruction
        associated.RequestDelete();
        return;
    }

    //Increment the previous arc by a fraction of PI, so it can rotate around the Alien
    arc += 0.5*M_PI;

    //Adujst the Minion rotation around it center
    associated.angleDeg = arc + 90;

    //Calculate the next Minion position
    Vec2 boxCenter = (*alienCenter.lock()).box.RectCenter();  
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
    //Bullet spawn at minion center
    bulletGO->box.x = (associated.box.RectCenter()).x;    
    bulletGO->box.y = (associated.box.RectCenter()).y;   
    //Bullet angle is the angle between the origin and the target,
    //Chosen values for speed, damage and maxDistance: 400, 5 and 400,
    Bullet *bullet = new Bullet(*bulletGO,target.DegPntsVec2(associated.box.RectCenter()),400,5,400,
                                "Recursos/img/minionbullet2.png",3,0.5,true);
    bulletGO->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(bulletGO);

}

void Minion::NotifyCollision(GameObject& other) {

}