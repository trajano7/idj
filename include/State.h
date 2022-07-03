#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"

#define INCLUDE_SDL 
#include "SDL_include.h"

using namespace std;

//State class represents a game screen and it state
class State {

    private:

        //Sprite bg;
        Music music;
        bool quitRequested;
        vector<unique_ptr<GameObject>> objectArray;

    public:

        State();
        ~State();

        //Preload all assets of the state
        void LoadAssets();
        //Update the state objects
        void Update(float dt);
        //Render the state sprites
        void Render();
        //Flag that store the quit request state
        bool QuitRequested();
        void Input();
        void AddObject(int mouseX, int mouseY);

};

#endif