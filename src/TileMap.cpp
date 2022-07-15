
#include <fstream>
#include <string>
#include <sstream>

#include "TileMap.h"

using namespace std;

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated) {

    Load(file);

}

void TileMap::Load(string file) {

    string line, word;
    int aux[3];

    fstream tm ("Recursos/map/tileMap.txt", ios::in);
    if(!tm.is_open()) {
        SDL_Log("Erro ao abrir o tile map.");
        exit(0);
    }

    //Gets the file header: width, height and depth
    getline(tm, line);
    stringstream str(line);
    for (int i=0; i<3; i++) {
        getline(str, word, ',');
        aux[i] = stoi(word);
    }
    getline(tm,line); //blank line

    mapWidth = aux[0];
    mapHeight = aux[1];
    mapDepth = aux[2]; 

    //Gets the matrix
    for (int i=0; i<mapDepth; i++) {
        for (int j=0; j<mapHeight; j++) {
            getline(tm, line);
            stringstream str(line);
            for (int k=0; k<mapWidth; k++) {
                getline(str, word, ',');
                if (word == "") break;
                //cout << word << " ";
                tileMatrix.push_back(stoi(word)-1);
            }
            //cout << endl;
        }
        //cout << endl;
        getline(tm,line); //blank line 
    }

    return;

}

void TileMap::SetTileSet(TileSet* tileSet) {

    this->tileSet = tileSet;

    return;

}

int& TileMap::At(int x, int y, int z) {

    int index, matrixSize;

    matrixSize = mapWidth*mapHeight;
    index = x + mapWidth*y + matrixSize*z;

    return tileMatrix[index];

}

