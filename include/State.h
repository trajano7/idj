#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

#define INCLUDE_SDL 
#include "SDL_include.h"

class State {

    private:

        Sprite bg;
        Music music;
        bool quitRequested;

    public:

        State();
        void LoadAssets();
        void Update(float dt);
        void Render();
        bool QuitRequested();

};

#endif