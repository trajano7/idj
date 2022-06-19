#include "State.h"

State::State() : bg("Recursos/img/ocean.jpg"), music("Recursos/audio/stageState.ogg") {

    quitRequested = false;
    music.Play(-1);

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

    bg.Render(0,0);

    return;

}

bool State::QuitRequested() {

    return quitRequested;

}