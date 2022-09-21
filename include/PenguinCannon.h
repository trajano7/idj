#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include "Component.h"
#include "Timer.h"

using namespace std;

//Player class that can be controlled to aim and shoot
class PenguinCannon : public Component {

    public:

        PenguinCannon(GameObject& associated, weak_ptr<GameObject> PenguinBody);

        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);
        void NotifyCollision(GameObject& other);

        void Shoot();
        
    private:

        //Reference to PenguinBody class
        weak_ptr<GameObject> pbody;
        float angle; //Aim and shoot angle
        Timer cooldown; //Counts the cooldown between shoots


};

#endif