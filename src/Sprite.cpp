#define INCLUDE_SDL_IMAGE

#include "Sprite.h"
#include "Game.h"

#include <typeinfo>

Sprite::Sprite(GameObject &associated) : Component(associated) {

    texture = nullptr;

}

Sprite::Sprite(string file, GameObject &associated) : Component(associated) {

    texture = nullptr;
    Open(file);
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();

}

Sprite::~Sprite() {

    if (IsOpen()) SDL_DestroyTexture(texture);

}

void Sprite::Open(string file) {

    if (IsOpen()) SDL_DestroyTexture(texture);

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (!IsOpen()) {
        SDL_Log("Unable to load texture: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (SDL_QueryTexture(texture,nullptr,nullptr,&width,&height) != 0) {
        SDL_Log("Unable to query texture: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SetClip(0,0,GetWidth(),GetHeight());

    return;

}

void Sprite::SetClip(int x, int y, int w, int h) {

    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    return;

}

void Sprite::Render() {

    //dstrect indicates the render position of the sprite
    SDL_Rect dstrect;

    dstrect.x = associated.box.x; 
    dstrect.y = associated.box.y; 
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstrect);

}

int Sprite::GetWidth() {

    return width;

}

int Sprite::GetHeight() {

    return height;

}

bool Sprite::IsOpen() {

    if (texture == nullptr) {
        return false;
    }

    return true;

}

void Sprite::Update(float dt) {

    return;

}

bool Sprite::Is(string type) {

    if("Sprite" == type) {
        return true;
    }

    return false;

}