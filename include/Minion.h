#ifndef MINION_H
#define MINION_H

#include "Component.h"

#include <string>

using namespace std;

class Minion : public Component {

    public:

        Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg);
        
        void Update(float dt);
        void Render();
        bool Is(string type);
        void Shoot(Vec2 target);

    private:

        weak_ptr<GameObject> alienCenter;
        float arc;

};

#endif