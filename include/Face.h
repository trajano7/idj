#ifndef FACE_H
#define FACE_H

#include "Component.h"

//Class that represents a enemy
class Face : public Component {

    public:

        Face(GameObject& associated);

        void Damage(int damage);

        void Update(float dt);
        void Render();
        bool Is(string type);

    private: 

        int hitpoints;

};

#endif