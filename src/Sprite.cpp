#define INCLUDE_SDL_IMAGE

#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

#include <typeinfo>

Sprite::Sprite(GameObject &associated) : Component(associated) {

    texture = nullptr;
    //Original scale as default
    scale.x = 1;
    scale.y = 1;

}

Sprite::Sprite(string file, GameObject &associated, int frameCount, float frameTime) : Component(associated) {

    texture = nullptr;
    //Original scale as default
    scale.x = 1;
    scale.y = 1;

    this->frameCount = frameCount;
    this->frameTime = frameTime;
    currentFrame = 0;
    timeElapsed = 0;

    Open(file);
    associated.box.w = width/frameCount;
    associated.box.h = height;

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

    SetClip(0,0,width/frameCount,height);

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
    //Render width and height adujsted with the scale
    dstrect.w = clipRect.w*scale.x;
    dstrect.h = clipRect.h*scale.y;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);

    return;

}

int Sprite::GetWidth() {

    return (width/frameCount)*scale.x;

}

int Sprite::GetHeight() {

    return height*scale.y;

}

bool Sprite::IsOpen() {

    if (texture == nullptr) {
        return false;
    }

    return true;

}

void Sprite::Update(float dt) {
    
    timeElapsed += dt;
    if (timeElapsed >= frameTime) {
        int frameSize = width/frameCount;
        SetClip(frameSize*currentFrame,0,frameSize,height);
        timeElapsed = 0;
        currentFrame = currentFrame == frameCount-1 ? 0 : currentFrame+1;
        //SDL_Log("current frame = %d\n", currentFrame);
    }
    
    return;

}

bool Sprite::Is(string type) {

    if("Sprite" == type) {
        return true;
    }

    return false;

}

void Sprite::SetScaleX(float scaleX, float scaleY) {

    scale.x = scaleX == 0 ? 1 : scaleX;
    scale.y = scaleY == 0 ? 1 : scaleY;
    associated.box.w *= scale.x; 
    associated.box.h *= scale.y;
    associated.box.x -= (scale.x-1)*(width/2);  
    associated.box.y -= (scale.y-1)*(height/2);  

    return;

}

void Sprite::SetFrame(int frame) {

    if (frame < frameCount) {
        currentFrame = frame;
        int frameSize = width/frameCount;
        SetClip(frameSize*currentFrame,0,frameSize,height);
        currentFrame = currentFrame == frameCount-1 ? 0 : currentFrame+1;
    }
    else {
        SDL_Log("SetFrame: Invalid operation, the frame %d doesn't exist for this sprite\n", frame);
    }

}


void Sprite::SetFrameCount(int frameCount) {

    this->frameCount = frameCount;
    associated.box.x = (width/frameCount)*scale.x;
    SetFrame(0);

}

void Sprite::SetFrameTime(float frameTime) {

    this->frameTime = frameTime;
    
}