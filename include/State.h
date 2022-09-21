#ifndef STATE_H
#define STATE_H

#include <vector>

#include "GameObject.h"

using namespace std;

//Superclass that declare all basic methods for any state
class State {

    public:

        State();
        virtual ~State();

        virtual void LoadAssets() = 0;
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;

        //Methods used when the stateStack change
        virtual void Start() = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;

        //Add and get objects form the object array
        virtual weak_ptr<GameObject> AddObject(GameObject* object);
        virtual weak_ptr<GameObject> GetObjectPtr(GameObject *object);

        //Used by Game to check if some pop or quit request was made by the state
        bool PopRequested();
        bool QuitRequested();

    protected:

        //Methods that start, update and render all objects in array
        void StartArray();
        virtual void UpdateArray(float dt);
        virtual void RenderArray();

        bool popRequested;
        bool quitRequested;
        bool started;

        vector<shared_ptr<GameObject>> objectArray;

};

#endif