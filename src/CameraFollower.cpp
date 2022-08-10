#include "CameraFollower.h"
#include "Camera.h"


CameraFollower::CameraFollower(GameObject& associated) : Component(associated) {

}

void CameraFollower::Update(float dt) {

    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;

    return;

}

void CameraFollower::Render() {
    
    return;

}

bool CameraFollower::Is(string type) {

    if("CameraFollower" == type) {
        return true;
    }

    return false;

}