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
        soundComponent = associated.GetComponent("Sound");
        if (soundComponent != nullptr) {
            sound = static_cast<Sound*>(soundComponent);
            if (!(sound->IsPlaying())) //if to do not repeat the sound while it play
                sound->Play(1);
        }
    }

    return;

}

void Face::Update(float dt) {

    Sound* sound = static_cast<Sound*>(associated.GetComponent("Sound"));

    //Wait for the death sound stop play to be deleted
    if (hitpoints <= 0 && !(sound->IsPlaying())) associated.RequestDelete();
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