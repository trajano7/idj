#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Game.h"

#include "Vec2.h"
#include "Rect.h"
#include <iostream>
 
int main(int argc, char *argv[]) {
    /*
    Game game = Game::GetInstance();
    game.Run();   
    */

    Vec2 teste(4,14);
    Vec2 teste2(3,2);
    Rect teste3(1,2,5,5);

    Vec2 teste4 = teste - teste2;

    std::cout << teste4.x << " " << teste4.y << "\n";
    std::cout << teste2.x << " " << teste2.y << "\n";
    teste2 = teste;
    std::cout << teste2.x << " " << teste2.y << "\n";

    //teste = teste3.RectCenter();

    //std::cout << teste.x << " | " << teste.y << "\n";

    //teste2 = teste.RotateVec2(270);
    //std::cout << teste2.DegVec2() << "\n";
    //std::cout << teste.DegVec2() << "\n";

 
    return 0;

}