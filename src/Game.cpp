#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF

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

    if (TTF_Init() != 0) {
        SDL_Log("SDL_TTF initialization failed: %s", SDL_GetError()); 
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

    storedState = nullptr;

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

    //Free storedState and pop all stack
    if (storedState != nullptr) free(storedState);
    while (!stateStack.empty()) stateStack.pop();

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();

    SDL_Quit();

}

State& Game::GetState() {

    return *(stateStack.top()).get();

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

void Game::Push(State* state) {

    storedState = state;

}

void Game::Run() {

    InputManager &inputManager = InputManager::GetInstance();

    //Push the initial state
    if (storedState == nullptr) {
        SDL_Log("Initial state not found\n");
        return;
    }
    stateStack.push(unique_ptr<State>(storedState));
    storedState = nullptr;

    frameStart = SDL_GetTicks();

    stateStack.top()->Start();
    //Runs until the current active state change the quit flag or if there is no states in stack 
    while (!stateStack.top()->QuitRequested() &&  !stateStack.empty()) {

        //Check if the current active state requested pop
        if (stateStack.top()->PopRequested()) {
            stateStack.pop();
            //Clear unused resources of poped states
            Resources::ClearImages();
            Resources::ClearMusics();
            Resources::ClearSounds();
            Resources::ClearFonts();
            if (stateStack.empty()) break;
            stateStack.top()->Resume();
        }
        //Check if there is some storedState to be pushed
        if (storedState != nullptr) {
            stateStack.top()->Pause();
            stateStack.push(unique_ptr<State>(storedState));
            storedState = nullptr;
            stateStack.top()->Start();
        }

        CalculateDeltaTime();
        inputManager.Update();
        stateStack.top()->Update(dt);
        stateStack.top()->Render();

        SDL_RenderPresent(renderer);

        //33 ms delay, mantain about 30 FPS
        SDL_Delay(33);

    }

    //Clear the stateStack
    while (!stateStack.empty()) stateStack.pop();

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();
    
}

