#ifndef MINION_H
#define MINION_H

#include "Component.h"

#include <string>

using namespace std;

// Component that implement an enemy minion that follow the Alien component
class Minion : public Component {

    private:

        // Reference to the Alien that it orbits
        weak_ptr<GameObject> alienCenter;
        // Current arc traveled by the minion around the Alien
        float arc;

    public:

        Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg);

        void Update(float dt);
        void Render();
        bool Is(string type);
        void Shoot(Vec2 target);
        void NotifyCollision(GameObject& other);
        
};

#endif