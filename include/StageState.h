#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <memory>
#include <vector>

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "TileSet.h"
#include "State.h"

#define INCLUDE_SDL 
#include "SDL_include.h"

using namespace std;

//State subclass that implements the game stage state
class StageState : public State {

    public:

        StageState();
        ~StageState();

        //Preload all assets of the state
        void LoadAssets();
        //Update the state objects
        void Update(float dt);
        //Render the state sprites
        void Render();
        //Flag that store the quit request state

        void Start();
        void Pause();
        void Resume();  
        
    private:

        //Background music;
        Music backgroundMusic;
        TileSet* tileSet;
        

        
};

#endif