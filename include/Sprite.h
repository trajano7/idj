#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"

#include <string>

using namespace std;

#define INCLUDE_SDL 
#include "SDL_include.h"

//Sprite is a child class of Component, it has one SDL_Texture (a image) and the methods to the methods to manipulate it
class Sprite : public Component {

    private:

        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
        //Render scale of the sprite
        Vec2 scale;

        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;
        
    public: 

        //Receive in the constructor the GameObject that will store the sprite
        Sprite(GameObject &associated);
        Sprite(string file, GameObject &associated, int frameCount, float frameTime);
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
        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScale();

        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);

};

#endif