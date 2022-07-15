#ifndef TILE_SET_H
#define TILE_SET_H

#include <string>

#include "Sprite.h"

using namespace std;

class TileSet {

    private:

        Sprite tileSet;
        int rows;
        int columns;
        int tileWidth;
        int tileHeight;

    public:

        TileSet(int tileWidth,int tileHeight, string file);

        void RenderTile(unsigned int index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();

};

#endif