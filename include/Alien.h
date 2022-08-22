#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "Vec2.h"

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

    private:

        //Class visible only to Alien, indicate a Alien action
        class Action {

            public:

                enum ActionType {
                    MOVE = 0,
                    SHOOT = 1
                };
                ActionType type;
                //Position where the action happened
                Vec2 pos;

                Action(ActionType type, float x, float y);

        };

        //Alien movement speed
        Vec2 speed;
        //Alien health points
        int hp;
    
        //Actions to be done
        queue<Action> taskQueue;
        //Each Alien has some Minions objects that follow it
        vector<weak_ptr<GameObject>> minionArray;

};

#endif