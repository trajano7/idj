#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include "GameObject.h"

using namespace std;

//Component is the base class for all components
class Component {

    public:

        Component(GameObject& associated);
        virtual ~Component();

        //Virtual pure methods, must be implemented in child classes
        virtual void Start();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(string type) = 0;
        //Notify that a collision occured with it associated, so it can take some action
        virtual void NotifyCollision(GameObject& other);

    protected:

        //Hold the GameObject that contains the component instance
        GameObject& associated;


};


#endif