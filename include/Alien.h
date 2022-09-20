#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

#include <string>
#include <queue>
#include <vector>

using namespace std;

//Component that implements an enemy behavior
class Alien : public Component {

    public:

        Alien(GameObject& associated, int nMinions); 
        ~Alien();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);
        void NotifyCollision(GameObject& other);

        static int alienCount;

    private:

        //Indicates the states of the Alien behavior state machine 
        enum AlienState {
            MOVING= 0,
            RESTING = 1
        };

        AlienState state;
        Timer restTimer; //Counts time in rest state
        Vec2 destination; //Store player position

        //Alien movement speed
        Vec2 speed;
        //Alien health points
        int hp;
    
        //Each Alien has some Minions objects that follow it
        vector<weak_ptr<GameObject>> minionArray;

};

#endif