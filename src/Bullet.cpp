#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject& associated,
               float angle,
               float speed,
               int damage,
               float maxDistance,
               string sprite) : Component(associated) {

    Sprite *bulletSprite = new Sprite(sprite, associated);
    associated.AddComponent(bulletSprite); 

    associated.angleDeg = (double) angle; 

    Vec2 speedDir = Vec2(1,0).RotateVec2(angle);
    this->speed = speedDir.MultScaVec2(speed);
    this->damage = damage;
    distanceLeft = maxDistance;              

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