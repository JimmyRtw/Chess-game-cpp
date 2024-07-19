#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

#ifndef SOUND_H
#define SOUND_H

class Sounds
{
    // private:

    // SoundBuffer move_buff,capture_buff,undo_buff,redo_buff;
    // Sound move_Sound,capture_Sound,undo_Sound,redo_Sound;

    // string common_path = "./SOUNDS/";

    public:

    Sounds();

    void init_Sounds();

    void Sound_buff();
    void Sound_Sound();

    void play_capture_Sound();
    void play_move_Sound();
    void play_undo_Sound();
    void play_redo_Sound();

};

#endif // SOUND_H
