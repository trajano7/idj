#include "State.h"

State::State() : bg() {

    quitRequested = false;

}

void State::LoadAssets() {

    return;

}

void State::Update(float dt) {

    if (SDL_QuitRequested()) {
        quitRequested = true;
    }

}

void State::Render() {

    return;

}

bool State::QuitRequested() {

    return quitRequested;

}