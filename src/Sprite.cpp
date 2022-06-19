#define INCLUDE_SDL_IMAGE

#include "Sprite.h"

Sprite::Sprite() {

    texture = nullptr;

}

Sprite::Sprite(string file) {

    texture = nullptr;
    Open(file);

}

Sprite::~Sprite() {

    if (texture != nullptr) SDL_DestroyTexture(texture);

}

void Sprite::Open(string file) {

    if (texture != nullptr) SDL_DestroyTexture(texture);

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        SDL_Log("Unable to load texture: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);

}