#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"

Bullet::Bullet(GameObject& associated,
               float angle,
               float speed,
               int damage,
               float maxDistance,
               string sprite,
               int frameCount,
               float frameTime,
               bool targetsPlayer) : Component(associated) {

    Sprite *bulletSprite = new Sprite(sprite, associated, frameCount, frameTime,-1);
    associated.AddComponent(bulletSprite); 
    bulletSprite->SetScaleX(1.5,1.5);
    Collider *collider = new Collider(associated,Vec2(1,1),Vec2(0,0));
    associated.AddComponent(collider);

    associated.angleDeg = (double) angle; 

    //Define the bullet speed module and angle
    Vec2 speedDir = Vec2(1,0).RotateVec2(angle);
    this->speed = speedDir.MultScaVec2(speed);
    this->damage = damage;
    distanceLeft = maxDistance;   
    //Defines who shoot the bullet  
    this->targetsPlayer = targetsPlayer;        

}

void Bullet::Update(float dt) {

    distanceLeft -= speed.MultScaVec2(dt).ModVec2();
    if(distanceLeft <= 0) {
        associated.RequestDelete();
        return;
    }

    associated.box.x += speed.x*dt;
    associated.box.y += speed.y*dt;

}

void Bullet::Render() {

}

bool Bullet::Is(string type) {

    if("Bullet" == type) {
        return true;
    }

    return false;    

}

int Bullet::GetDamage() {

    return damage;

}

void Bullet::NotifyCollision(GameObject& other) {

    //Check if other is a Penguin and the bullet was shot by the Alien
    //Or if other is Alien and the bullet was shot by the Penguin
    if ((other.GetComponent("PenguinCannon") != nullptr && targetsPlayer) ||
         (other.GetComponent("Alien") != nullptr && !targetsPlayer)) {
          associated.RequestDelete();
    }

}