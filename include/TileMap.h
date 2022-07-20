#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>
#include <string>

#include "TileSet.h"
#include "GameObject.h"

using namespace std;

//Class that maps the tile set to form a scenario in the window 
class TileMap : public Component {

    public:

        TileMap(GameObject& associated, string file, TileSet* tileSet);
        
        //Load tileMap file
        void Load(string file);
        void SetTileSet(TileSet* tileSet);
        //tileMap is stored in a 1D vector, so this function calculate a single index based on coordinates
        int& At(int x, int y, int z);
        //Render a single layer from the tileMap
        void RenderLayer(int layer, int cameraX, int cameraY );
        int GetWidth();
        int GetHeight();
        int GetDepth();

        //Virtual method from the base class:
        //Render all layers from tile map
        void Render();
        void Update(float dt);
        bool Is(string type);

    private:

        //Store the tileMap matrix in a 1D vector
        vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;

};

#endif