#ifndef GAME_H
#define GAME_H

#include <string>
#include <stack>

#define INCLUDE_SDL 
#include "SDL_include.h"

#include "State.h"

using namespace std;

//Game class intializate SDL resources and run the main game loop
class Game {
    
    public: 

        ~Game();

        SDL_Renderer* GetRenderer();
        //Static method that guarantee the singleton pattern
        static Game& GetInstance();
        State& GetState();
        //Receive a new state to be pushed in stateStack from other states 
        void Push(State* state);

        //Method that keeps the main game loop
        void Run();
        float GetDeltaTime();
        
    private:

        Game(string title, int width, int height);

        //Using singleton pattern
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        //Store some state that must be pushed in stateStack 
        State* storedState;
        //This stack stores the game states, only the top is active
        stack<unique_ptr<State>> stateStack;

        //Store the last frame start time
        int frameStart;
        //Store the time difference between the last and current frame
        float dt;

        //Calculates time between frames
        void CalculateDeltaTime();


};

#endif