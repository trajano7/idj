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

//This class is responsable to read and store the input state each frame
class InputManager {

    public:

        //Singleton pattern
        static InputManager& GetInstance();
        ~InputManager();

        void Update();

        //Check keyboard input
        bool KeyPress(int key);
        bool KeyRealease(int key);
        bool IsKeyDown(int key);

        //Check mouse input
        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);

        //Get the postion of the mouse relative to the game window
        int GetMouseX();
        int GetMouseY();
        
        bool QuitRequested();

    private:

        //Read the input events and store it
        InputManager();

        //Update structures store the frame that some input update happened and State store if some button its pressed or not
        bool mouseState[6];
        int mouseUpdate[6];
        unordered_map<int, bool> keyState;
        unordered_map<int, int> keyUpdate;
        bool quitRequested;
        //Counts the frames
        int updateCounter;
        //Postion of the mouse relative to the game window
        int mouseX;
        int mouseY;

};

#endif