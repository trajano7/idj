#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

#include <unordered_map>

#define INCLUDE_SDL 
#include "SDL_include.h"

using namespace std;

class InputManager {

    public:

        static InputManager& GetInstance();
        ~InputManager();

        void Update();

        bool KeyPress(int key);
        bool KeyRealease(int key);
        bool IsKeyDown(int key);

        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);

        int GetMouseX();
        int GetMouseY();
        
        bool QuitRequested();

    private:

        InputManager();

        bool mouseState[6];
        int mouseUpdate[6];
        unordered_map<int, bool> keyState;
        unordered_map<int, int> keyUpdate;
        bool quitRequested;
        int updateCounter;
        int mouseX;
        int mouseY;

};

#endif