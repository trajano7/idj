#include "Resources.h"

#include "Game.h"

unordered_map<std::string, SDL_Texture*> Resources::imageTable = {};
unordered_map<std::string, Mix_Music*> Resources::musicTable = {};
unordered_map<std::string, Mix_Chunk*> Resources::soundTable = {};

SDL_Texture* Resources::GetImage(string file) {

    unordered_map<std::string, SDL_Texture*>::const_iterator img;
    SDL_Texture* texture;

    img = imageTable.find(file);
    if (img == imageTable.end()) {
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if (texture == nullptr) {
            SDL_Log("Unable to load texture: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        imageTable.emplace(file,texture);
    }

    return imageTable.at(file);
            
}

Mix_Music* Resources::GetMusic(string file) {

    unordered_map<std::string, Mix_Music*>::const_iterator msc;
    Mix_Music* music;

    msc = musicTable.find(file);
    if (msc == musicTable.end()) {
        music = Mix_LoadMUS(file.c_str());
        if (music == nullptr) {
            SDL_Log("Unable to load music: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        musicTable.emplace(file,music);
    }

    return musicTable.at(file);

}

Mix_Chunk* Resources::GetSound(string file) {

    unordered_map<std::string, Mix_Chunk*>::const_iterator snd;
    Mix_Chunk* chunk;

    snd = soundTable.find(file);
    if (snd == soundTable.end()) {
        chunk = Mix_LoadWAV(file.c_str());
        if (chunk == nullptr) {
            SDL_Log("Unable to load chunk: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        soundTable.emplace(file,chunk);
    }

    return soundTable.at(file);

}

void Resources::ClearImages() {

    unordered_map<std::string, SDL_Texture*>::const_iterator img;

    for (img = imageTable.begin(); img != imageTable.end(); img++) {
        SDL_DestroyTexture(img->second);
    }

}

void Resources::ClearMusics() {

    unordered_map<std::string, Mix_Music*>::const_iterator msc;

    for (msc = musicTable.begin(); msc != musicTable.end(); msc++) {
         Mix_FreeMusic(msc->second);
    }

}

void Resources::ClearSounds() {

    unordered_map<std::string, Mix_Chunk*>::const_iterator snd;

    for (snd = soundTable.begin(); snd != soundTable.end(); snd++) {
         Mix_FreeChunk(snd->second);
    }

}

