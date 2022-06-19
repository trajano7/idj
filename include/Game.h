#ifndef GAME_H
#define GAME_H

#include <string>

#define INCLUDE_SDL 
#include "SDL_include.h"

#include "State.h"

using namespace std;

class Game {
    private:

        Game(string title, int width, int height);

        //Use singleton pattern
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

    public: 

        ~Game();
        SDL_Renderer* GetRenderer();
        static Game& GetInstance();
        State& GetState();
        void Run();

};

#endif