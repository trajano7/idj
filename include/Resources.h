#ifndef RESOURCES_H
#define RESOURCES_H

#include <unordered_map>
#include <string>

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"


using namespace std;

class Resources {

    private:

      static unordered_map<std::string, SDL_Texture*> imageTable;
      static unordered_map<std::string, Mix_Music*> musicTable;
      static unordered_map<std::string, Mix_Chunk*> soundTable;

    public:

      static SDL_Texture* GetImage(string file);
      static Mix_Music* GetMusic(string file);
      static Mix_Chunk* GetSound(string file);

      static void ClearImages();
      static void ClearMusics();
      static void ClearSounds();

};


#endif