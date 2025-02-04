#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <memory>

using namespace std;

#define INCLUDE_SDL 
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

//Music class has one music and the methods to the methods to manipulate it
class Music {

    public:

        Music();
        Music(string file);
        ~Music();

        //Open the music
        void Open(string file);
        //Check if the music is loaded
        bool IsOpen();
        //Play the music
        void Play(int times);
        //Stop the music
        void Stop(int msToStop);
        
    private:

        shared_ptr<Mix_Music> music;




};

#endif