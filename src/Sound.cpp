#include "Sound.h"
#include "Resources.h"

Sound::Sound(GameObject& associated) : Component(associated) {

    chunk = nullptr;

}

Sound::Sound(GameObject& associated, string file) : Component(associated) {

    chunk = nullptr;
    Open(file);

}

Sound::~Sound() {

    Stop();
    //if (IsOpen()) Mix_FreeChunk(chunk);

}

void Sound::Open(string file) {
    
    chunk = Resources::GetSound(file);

    return;

} 

void Sound::Play(int times) {

    if (IsOpen()) {
        channel = Mix_PlayChannel(-1,chunk.get(),times-1);
        if (channel == -1) {
            SDL_Log("Unable to play the sound: %s", SDL_GetError());
            exit(EXIT_FAILURE);  
        }
    }

    return;

}

void Sound::Stop() {

    if(IsOpen()) {
       Mix_HaltChannel(channel);
    }

}

bool Sound::IsPlaying() {

    if (Mix_Playing(channel) != 0) return true;

    return false;

}

bool Sound::IsOpen() {

    if (chunk == nullptr) {
       return false;
    }

    return true;

}

void Sound::Update(float dt) {

    return;

}

void Sound::Render() {

    return;

}

bool Sound::Is(string type) {

    if("Sound" == type) {
        return true;
    }

    return false;

}