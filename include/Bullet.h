#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"

#include <string>

using namespace std;

//Component that implements a projectile behavior
class Bullet : public Component {

    public:

        Bullet(GameObject& associated,
               float angle,
               float speed,
               int damage,
               float maxDistance, //Max distance that the bullet can travel
               string sprite,
               int frameCount,
               float frameTime,
               bool targetsPlayer);
        
        void Update(float dt);
        void Render();
        bool Is(string type);
        int GetDamage();
        void NotifyCollision(GameObject& other);

        //Used to know who shoot the bullet 
        //Player -> false and Alien -> true
        bool targetsPlayer;

    private:

        Vec2 speed;
        float distanceLeft;
        int damage;

};

#endif