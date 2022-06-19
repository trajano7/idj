#ifndef MUSIC_H
#define MUSIC_H

#include <string>

using namespace std;

#define INCLUDE_SDL 
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music {

    private:

        Mix_Music* music;

    public:

        Music();
        Music(string file);
        ~Music();

        void Open(string file);
        bool IsOpen();
        void Play(int times);
        void Stop(int msToStop);



};

#endif