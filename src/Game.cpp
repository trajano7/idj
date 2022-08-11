#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE

#include <iostream>
#include "Game.h"

#include "TileSet.h"
#include "TileMap.h"
#include "Resources.h"
#include "InputManager.h"

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height) {

    int bitmask;

    //Check if already have an instance of Game
    if (instance != nullptr) {
        exit(EXIT_FAILURE);
    }

    instance = this;

    //Initialize SDL libs
    if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    bitmask = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    if (IMG_Init(bitmask) != bitmask) {
        SDL_Log("SDL_image initialization failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (Mix_Init(MIX_INIT_OGG) == 0) {
        SDL_Log("SDL_mix initialization failed: %s", SDL_GetError()); 
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) != 0) {
        SDL_Log("OpenAudio initialization failed: %s", SDL_GetError()); 
        exit(EXIT_FAILURE);
    }

    Mix_AllocateChannels(32);

    //Create SDL window and renderer
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    state = new State();

    frameStart = SDL_GetTicks();
    dt = 0;

}

Game& Game::GetInstance() {

    if (instance == nullptr) {
        instance = new Game("Matheus_170152227", 1024, 600);
    }

    return *instance;

}

Game::~Game() {

    free(state);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();

    SDL_Quit();

}

State& Game::GetState() {

    return *state;

}

SDL_Renderer* Game::GetRenderer() {
    
    return renderer;

}

void Game::CalculateDeltaTime() {

    int oldFrameStart = frameStart;
    //Get current frame time
    frameStart = SDL_GetTicks();

    //dt in seconds
    dt = (float) (frameStart - oldFrameStart)/1000;

} 

void Game::Run() {

    InputManager &inputManager = InputManager::GetInstance();

    frameStart = SDL_GetTicks();

    //Runs until the current active state change the quit flag
    while (!state->QuitRequested()) {

        CalculateDeltaTime();
        inputManager.Update();
        state->Update(dt);
        state->Render();

        SDL_RenderPresent(renderer);

        //33 ms delay, mantain about 30 FPS
        SDL_Delay(33);

    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    
}

