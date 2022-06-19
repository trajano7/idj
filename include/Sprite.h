#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "Game.h"

using namespace std;

#define INCLUDE_SDL 
#include "SDL_include.h"

class Sprite {

    private:

        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
        
    public: 

        Sprite();
        Sprite(string file);
        ~Sprite();
        void Open(string file);

};

#endif