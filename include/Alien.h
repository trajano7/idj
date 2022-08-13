#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "Vec2.h"

#include <string>
#include <queue>
#include <vector>

using namespace std;

class Alien : public Component {

    public:

        Alien(GameObject& associated, int nMinions); 
        ~Alien();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);

    private:

        class Action {

            public:

                enum ActionType {
                    MOVE = 0,
                    SHOOT = 1
                };
                ActionType type;
                Vec2 pos;

                Action(ActionType type, float x, float y);

        };

        Vec2 speed;
        int hp;

        queue<Action> taskQueue;
        vector<weak_ptr<GameObject>> minionArray;

};

#endif