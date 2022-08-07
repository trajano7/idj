#include "InputManager.h"

InputManager& InputManager::GetInstance() {

    static InputManager inputManager;

    return inputManager;

}

InputManager::InputManager() {

    for (int i; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }

    quitRequested = false;
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;

}

InputManager::~InputManager() {

}

void InputManager::Update() {

    SDL_Event event;

    SDL_GetMouseState(&mouseX,&mouseY);
    quitRequested = false;
    updateCounter++;

    while (SDL_PollEvent(&event)) { 
        switch (event.type) {
            case SDL_KEYDOWN:
                SDL_Log("KEYDOWN\n");
                if (!event.key.repeat) { 
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                }
                break;
            case SDL_KEYUP:
                SDL_Log("KEYUP\n");
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            case SDL_QUIT:
                SDL_Log("QUIT\n");
                quitRequested = true;
                break;
            default:
                //SDL_Log("Unhandled event\n");
                break;
        }
    }

    return;

}

bool InputManager::KeyPress(int key) {

    return keyState[key] ? keyUpdate[key] == updateCounter : false;

}

bool InputManager::KeyRealease(int key) {

    return !keyState[key] ? keyUpdate[key] == updateCounter : false;
   
}

bool InputManager::IsKeyDown(int key) {

    return keyState[key];

}

bool InputManager::MousePress(int button) {

    return mouseState[button] ? mouseUpdate[button] == updateCounter : false;

}

bool InputManager::MouseRelease(int button) {

    return !mouseState[button] ? mouseUpdate[button] == updateCounter : false;

}

bool InputManager::IsMouseDown(int button) {

    return mouseState[button];

}

int InputManager::GetMouseX() {

    return mouseX;

}

int InputManager::GetMouseY() {

    return mouseY;

}

bool InputManager::QuitRequested() {
    
    return quitRequested;

}