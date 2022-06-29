#include "Face.h"

#include "Sound.h"

Face::Face(GameObject& associated) : Component(associated) {
    
    hitpoints = 30;

}

void Face::Damage(int damage) {

    Component* soundComponent;
    Sound* sound;

    hitpoints -= damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        soundComponent = associated.GetComponent("Sound");
        if (sound != nullptr) {
            sound = static_cast<Sound*>(soundComponent);
            sound->Play(1);
        }
    }

    return;

}

void Face::Update(float dt) {

    return;

}

void Face::Render() {

    return;

} 

bool Face::Is(string type) {

    if("Face" == type) {
        return true;
    }

    return false;

}