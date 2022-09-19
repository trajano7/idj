#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include "Component.h"

using namespace std;

class PenguinCannon : public Component {

    private:

        weak_ptr<GameObject> pbody;
        float angle;

    public:

        PenguinCannon(GameObject& associated, weak_ptr<GameObject> PenguinBody);

        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);

        void Shoot();

};

#endif