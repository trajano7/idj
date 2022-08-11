#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include <string>

#include "Component.h"

using namespace std;

//This component makes the GameObject follow the Camera position
class CameraFollower : public Component {

    public:

        CameraFollower(GameObject& associated);

        void Update(float dt);
        void Render();
        bool Is(string type);

};

#endif
