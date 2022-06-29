#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Rect.h"
#include <vector>
#include <string>

using namespace std;

class Component;

class GameObject {

    public:

        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(string type);

        Rect box;

    private:

        vector <Component*> components;
        bool isDead;

};

#endif