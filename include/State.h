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

    public:

        State();
        ~State();

        //Preload all assets of the state
        void LoadAssets();
        void Start();
        //Update the state objects
        void Update(float dt);
        //Render the state sprites
        void Render();
        //Flag that store the quit request state
        bool QuitRequested();
        void Input();
        weak_ptr<GameObject> AddObject(GameObject *go);
        weak_ptr<GameObject> GetObjectPtr(GameObject *go);

    private:

        //Sprite bg;
        Music music;
        bool quitRequested;
        bool started;
        vector<shared_ptr<GameObject>> objectArray;
        

};

#endif