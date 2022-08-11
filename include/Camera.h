#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Vec2.h"

//Game camera, display a area of all game world in the window
class Camera {

    public:

        static void Follow(GameObject* newFocus);
        static void Unfollow();
        //Update Camera position. Can operate following a GameObject or moving freely
        static void Update(float dt);

        //Camera position relative to the world coordinates system
        static Vec2 pos;
        //Camera speed
        static Vec2 speed;

    private:

        //Camera can follow a specific GameObject
        static GameObject *focus;

};


#endif