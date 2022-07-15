#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>
#include <string>

#include "TileSet.h"
#include "GameObject.h"

using namespace std;

class TileMap : public Component {

    public:

        TileMap(GameObject& associated, string file, TileSet* tileSet);
        
        void Load(string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z);
        void RenderLayer(int layer, int cameraX, int cameraY );
        int GetWidth();
        int GetHeight();
        int GetDepth();

        //Virtual method from the base class:
        void Render();
        void Update(float dt);
        bool Is(string type);

    private:

        vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;

};

#endif