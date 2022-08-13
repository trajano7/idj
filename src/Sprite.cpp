#define INCLUDE_SDL_IMAGE

#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

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

     //if (IsOpen()) SDL_DestroyTexture(texture);

}

void Sprite::Open(string file) {
    
    texture = Resources::GetImage(file);

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

    // SDL_Log("Sprite: %f %f %f %f\n", associated.box.x, Camera::pos.x, associated.box.y, Camera::pos.y);

    //Adjust the render position based on Camera position
    Render(
     associated.box.x - Camera::pos.x
    ,associated.box.y - Camera::pos.y);

    return;

}

void Sprite::Render(float x, float y) {

    //dstrect indicates the render position of the sprite
    SDL_Rect dstrect;

    dstrect.x = x; 
    dstrect.y = y; 
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstrect);

    return;

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