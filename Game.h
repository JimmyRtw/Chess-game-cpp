#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Board.h"
#include "Piece.h"
#include "Play.h"
#include "Shapes.h"
#include "Internal_Chess_Board.h"
#include "Legal_Moves.h"
#include "Sound.h"
#include "Button.h"
#include "ScreenText.h"

using namespace std;
using namespace sf;

#ifndef GAME_H
#define GAME_H


class Game
{
    private:

    //basic game variables
    RenderWindow* window;
    Event event;
    int MX,MY;

    //game objects
    Board board;
    Piece piece;
    Play play;
    Shapes shape;
    Internal_Chess_Board icb;
    Legal_Moves lm;
    Sounds sound;

    public:

    bool white_turn = true;

    Game();

    void init_window();

    void Play_game();
    void Quit_game();

    void Game_loop();
    void update();
    void draw();

};

#endif // GAME_H
