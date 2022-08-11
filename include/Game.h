#ifndef GAME_H
#define GAME_H

#include <string>

#define INCLUDE_SDL 
#include "SDL_include.h"

#include "State.h"

using namespace std;

//Game class intializate SDL resources and run the main game loop
class Game {
    private:

        Game(string title, int width, int height);

        //Using singleton pattern
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

        //Store the last frame start time
        int frameStart;
        //Store the time difference between the last and current frame
        float dt;

        void CalculateDeltaTime();

    public: 

        ~Game();

        SDL_Renderer* GetRenderer();
        //Static method that guarantee the singleton pattern
        static Game& GetInstance();
        State& GetState();
        //Method that keeps the main game loop
        void Run();
        float GetDeltaTime();

};

#endif