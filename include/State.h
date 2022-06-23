#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

#define INCLUDE_SDL 
#include "SDL_include.h"

//State class represents a game screen and it state
class State {

    private:

        Sprite bg;
        Music music;
        bool quitRequested;

    public:

        State();

        //Preload all assets of the state
        void LoadAssets();
        //Update the state objects
        void Update(float dt);
        //Render the state sprites
        void Render();
        //Flag that store the quit request state
        bool QuitRequested();

};

#endif