#define INCLUDE_SDL_MIXER

#include "Music.h"

Music::Music() {

    music = nullptr;

}

Music::Music(string file) {

    music = nullptr;
    Open(file);

}

void Music::Open(string file) {

    music = Mix_LoadMUS(file.c_str());
    if (!IsOpen()) {
        SDL_Log("Unable to load music: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

}

Music::~Music() {

    Stop(1500);
    if (music != nullptr) Mix_FreeMusic(music);

}

bool Music::IsOpen() {

    if (music == nullptr) {
        return false;
    }

    return true;

}

void Music::Play(int times) {

    if (IsOpen()) {
        if (Mix_PlayMusic(music,times) == -1) {
            SDL_Log("Unable to play music: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }   

    return;

}

void Music::Stop(int msToStop) {

    if (Mix_FadeOutMusic(msToStop) == 0) {
        SDL_Log("Unable to stop music: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

}

