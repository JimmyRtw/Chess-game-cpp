#include "Sound.h"

Sounds::Sounds()
{
    init_Sounds();
}

void Sounds::init_Sounds()
{
    Sound_buff();
    Sound_Sound();
}

void Sounds::Sound_buff()
{
    // move_buff.loadFromFile(common_path+"move.wav");
    // capture_buff.loadFromFile(common_path+"capture.wav");
    // undo_buff.loadFromFile(common_path+"undo.wav");
    // redo_buff.loadFromFile(common_path+"redo.wav");
}

void Sounds::Sound_Sound()
{
    // move_Sound.setBuffer(move_buff);
    // capture_Sound.setBuffer(capture_buff);
    // undo_Sound.setBuffer(undo_buff);
    // redo_Sound.setBuffer(redo_buff);
}

void Sounds::play_capture_Sound()
{
    // capture_Sound.play();
}

void Sounds::play_move_Sound()
{
    // move_Sound.play();
}

void Sounds::play_undo_Sound()
{
    // undo_Sound.setVolume(4.00);
    // undo_Sound.play();
}

void Sounds::play_redo_Sound()
{
    // redo_Sound.setVolume(4.00);
    // redo_Sound.play();
}
