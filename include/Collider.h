#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include "Rect.h"

//This component determine the collision area of GameObjects
class Collider : public Component {

    private:

        Vec2 scale; //Collider scale in relation to GameObject size
        Vec2 offset; //Collider offset in relation to GameObject position

    public:

        Collider(GameObject& associated, Vec2 scale, Vec2 offset);
        
        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);
        void SetScale(Vec2 scale);
        void SetOffset(Vec2 offset);

        Rect box;

};

#endif