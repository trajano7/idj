#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include "GameObject.h"

using namespace std;

class Component {

    public:

        Component(GameObject& associated);
        virtual ~Component();

        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(string type) = 0;

    protected:

        GameObject& associated;


};


#endif