#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"

#include <string>

using namespace std;

#define INCLUDE_SDL 
#include "SDL_include.h"

//Sprite is a child class of Componen, it has one SDL_Texture (a image) and the methods to the methods to manipulate it
class Sprite : public Component {

    private:

        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
        
    public: 

        //Receive in the constructor the GameObject that will store the sprite
        Sprite(GameObject &associated);
        Sprite(string file, GameObject &associated);
        ~Sprite();

        //Open the image
        void Open(string file);
        //Delimits the texture area that will render
        void SetClip(int x, int y, int w, int h);
        int GetWidth();
        int GetHeight();
        //Check if the texture has some image loaded
        bool IsOpen();

        //Virtual method from the base class:
        //Adds the texture to the game renderer
        void Render();
        void Render(float x, float y);
        void Update(float dt);
        bool Is(string type);

};

#endif