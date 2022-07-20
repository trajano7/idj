#ifndef TILE_SET_H
#define TILE_SET_H

#include <string>

#include "Sprite.h"

using namespace std;

//Class that stores all the tiles of a set and can render them
class TileSet {

    public:

        TileSet(int tileWidth,int tileHeight, string file);

        //Render a single tile in position (x,y)
        void RenderTile(unsigned int index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();

    private:

        //Store the tiles as a single image but knows how to slice it
        Sprite tileSet;
        int rows;
        int columns;
        int tileWidth;
        int tileHeight;

        GameObject associatedAux;

};

#endif