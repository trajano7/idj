#include "Resources.h"

#include "Game.h"

#include <iostream>

unordered_map<std::string, shared_ptr<SDL_Texture>> Resources::imageTable = {};
unordered_map<std::string, shared_ptr<Mix_Music>> Resources::musicTable = {};
unordered_map<std::string, shared_ptr<Mix_Chunk>> Resources::soundTable = {};
unordered_map<std::string, shared_ptr<TTF_Font>>  Resources::fontTable = {};

shared_ptr<SDL_Texture> Resources::GetImage(string file) {

    unordered_map<std::string, shared_ptr<SDL_Texture>>::const_iterator img;
    SDL_Texture* texture;

    img = imageTable.find(file);
    
    if (img == imageTable.end()) {
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if (texture == nullptr) {
            SDL_Log("Unable to load texture: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        shared_ptr<SDL_Texture> shared_texture(texture, 
            [](SDL_Texture* texture) {SDL_DestroyTexture(texture);}
        ); 
        imageTable.emplace(file,shared_texture);
    }
    return imageTable.at(file);
            
}

shared_ptr<Mix_Music> Resources::GetMusic(string file) {

    unordered_map<std::string, shared_ptr<Mix_Music>>::const_iterator msc;
    Mix_Music* music;

    msc = musicTable.find(file);
    if (msc == musicTable.end()) {
        music = Mix_LoadMUS(file.c_str());
        if (music == nullptr) {
            SDL_Log("Unable to load music: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        shared_ptr<Mix_Music> shared_music(music, 
            [](Mix_Music* music) {Mix_FreeMusic(music);}
        ); 
        musicTable.emplace(file,shared_music);
    }

    return musicTable.at(file);

}

shared_ptr<Mix_Chunk> Resources::GetSound(string file) {

    unordered_map<std::string, shared_ptr<Mix_Chunk>>::const_iterator snd;
    Mix_Chunk* chunk;

    snd = soundTable.find(file);
    if (snd == soundTable.end()) {
        chunk = Mix_LoadWAV(file.c_str());
        if (chunk == nullptr) {
            SDL_Log("Unable to load chunk: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        shared_ptr<Mix_Chunk> shared_chunk(chunk, 
            [](Mix_Chunk* chunk) {Mix_FreeChunk(chunk);}
        ); 
        soundTable.emplace(file,shared_chunk);
    }

    return soundTable.at(file);

}

shared_ptr<TTF_Font> Resources::GetFont(string file, int fontSize) {

    unordered_map<std::string, shared_ptr<TTF_Font>>::const_iterator fnt;
    TTF_Font* font;
    string key = file + to_string(fontSize);

    fnt = fontTable.find(key);
    if (fnt == fontTable.end()) {
        font = TTF_OpenFont(file.c_str(), fontSize);
        if (font == nullptr) {
            SDL_Log("Unable to load font: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        shared_ptr<TTF_Font> shared_font(font, 
            [](TTF_Font* font) {TTF_CloseFont(font);}
        ); 
        fontTable.emplace(key,shared_font);
    }

    return fontTable.at(key);

}

void Resources::ClearImages() {

    unordered_map<std::string, shared_ptr<SDL_Texture>>::const_iterator img = imageTable.begin();

    while (img != imageTable.end()) {
        if (img->second.unique()) {
            img = imageTable.erase(img);
        }
        else img++;
    }

    imageTable.clear();

}

void Resources::ClearMusics() {

    unordered_map<std::string, shared_ptr<Mix_Music>>::const_iterator msc;

    while (msc != musicTable.end()) {
        if (msc->second.unique()) {
            msc = musicTable.erase(msc);
        }
        else msc++;
    }

    //musicTable.clear();

}

void Resources::ClearSounds() {

    unordered_map<std::string, shared_ptr<Mix_Chunk>>::const_iterator snd;

    while (snd != soundTable.end()) {
        if (snd->second.unique()) {
            snd = soundTable.erase(snd);
        }
        else snd++;
    }

    //soundTable.clear();

}

void Resources::ClearFonts() {

    unordered_map<std::string, shared_ptr<TTF_Font>>::const_iterator fnt;

    while (fnt != fontTable.end()) {
        if (fnt->second.unique()) {
            fnt = fontTable.erase(fnt);
        }
        else fnt++;
    }

    //fontTable.clear();

}

