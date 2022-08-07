#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Game.h"

#include "Vec2.h"
#include "Rect.h"
#include "TileSet.h"
#include "Sprite.h"
#include <iostream>
 
int main(int argc, char *argv[]) {

    Game& game = Game::GetInstance();
    game.Run(); 

    return 0;

}