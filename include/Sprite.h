#ifndef SPRITE_H
#define SPRITE_H

#include <string>

using namespace std;

#define INCLUDE_SDL 
#include "SDL_include.h"

//Music class has one SDL_Texture (a image) and the methods to the methods to manipulate it
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

        //Open the image
        void Open(string file);
        //Delimits the texture area that will render
        void SetClip(int x, int y, int w, int h);
        //Adds the texture to the game renderer
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        //Check if the texture has some image loaded
        bool IsOpen();

};

#endif