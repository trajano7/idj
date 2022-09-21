#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H

#include <string>

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

using namespace std;

//Player class that can be controlled to be moved around the map
class PenguinBody : public Component {

    public:

        PenguinBody(GameObject& associated);
        ~PenguinBody();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);
        void NotifyCollision(GameObject& other);

        //Used by enemies to locate the player
        Vec2 GetPenguinPos();

        //Keeps a static referece to itself, so it can be easily acessed by others classes
        static PenguinBody* player;
        
    private: 

        //Reference to PenguinCannon class
        weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;

        //Times a invincibility time for the penguin, to avoid receive damage in the spawn
        Timer invTimer; 


};

#endif