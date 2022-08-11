#include "Face.h"

#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"

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

    InputManager& inputManager = InputManager::GetInstance();

    //Check if the left mouse button was clicked in the current frame
    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        //Check if the click occurred in the Face
        if(associated.box.PointInRect( {(float) inputManager.GetMouseX() + Camera::pos.x, (float) inputManager.GetMouseY() + Camera::pos.y} )) {
		    //Compute the damage
		    Damage(std::rand() % 10 + 10);
		}
    }

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