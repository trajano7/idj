#ifndef RESOURCES_H
#define RESOURCES_H

#include <unordered_map>
#include <string>
#include <memory>

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"


using namespace std;

//Class stores all the image, msuic and sound information to avoid duplicated data
//All data and methods are static so the same object can be used by any class
//Its used shared_ptr to store so itens can be deleted when a unique ptr is left
class Resources {
  
    public:

      static shared_ptr<SDL_Texture> GetImage(string file);
      static shared_ptr<Mix_Music> GetMusic(string file);
      static shared_ptr<Mix_Chunk> GetSound(string file);
      static shared_ptr<TTF_Font> GetFont(string file, int fontSize);

      static void ClearImages();
      static void ClearMusics();
      static void ClearSounds();
      static void ClearFonts();

    private:

      static unordered_map<std::string, shared_ptr<SDL_Texture>> imageTable;
      static unordered_map<std::string, shared_ptr<Mix_Music>> musicTable;
      static unordered_map<std::string, shared_ptr<Mix_Chunk>> soundTable;
      static unordered_map<std::string, shared_ptr<TTF_Font>> fontTable;


};


#endif