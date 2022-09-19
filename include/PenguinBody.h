#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H

#include <string>

#include "Component.h"
#include "Vec2.h"

using namespace std;

class PenguinBody : public Component {

    private: 

        weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;

    public:

        PenguinBody(GameObject& associated);
        ~PenguinBody();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);

        static PenguinBody* player;

};

#endif