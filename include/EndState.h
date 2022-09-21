#ifndef END_STATE_H
#define END_STATE_H

#include "State.h"
#include "Music.h"

//State subclass that implements a end screen state
class EndState : public State {

    public:

        EndState();
        ~EndState();

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

        Music backgroundMusic;



};

#endif