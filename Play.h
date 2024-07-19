#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Shapes.h"
#include "Internal_Chess_Board.h"
#include "Piece.h"
#include "Legal_Moves.h"
#include "Sound.h"
#include "Special_Moves.h"
#include "Button.h"
#include "ScreenText.h"

using namespace std;
using namespace sf;

#ifndef PLAY_H
#define PLAY_H

class Play
{
    private:

    //parameters
    int n = 0,psm=0;
    bool is_move = false;
    bool white_turn = true;
    float ox,oy,nx,ny;

    Sprite* F_Pieces;
    Sprite* E_Pieces;

    //helping game object
    Piece* piece;
    Shapes* shape;
    Legal_Moves *lm;
    Internal_Chess_Board* icb;
    Sounds* sound;
    Special_Moves* sm;
    Button* Restart, *Quite;
    ScreenText *Last_Move,*Curr_Move,*Legal_moves,*Move_Count;

    string curr_fent_string = "";

    public:

    void Game(Sprite* white,Sprite* black,int MX,int MY,Event event,Shapes* SHAPE,Internal_Chess_Board* ICB,Piece* PIECE,Legal_Moves* LM,Sounds* SOUND,Button* Restart,Button* Quite_Game,ScreenText *Last_Move,ScreenText *Move,ScreenText *LEGAL_MOVES,ScreenText *MOVE_COUNT);
    void Restart_Game();

    void init_objects(Shapes* SHAPE,Internal_Chess_Board* ICB,Piece* PIECE,Legal_Moves* LM,Sounds* SOUND,Button* Restart,Button* QUITE,ScreenText *LAST_MOVE,ScreenText *MOVE,ScreenText *LEGAL_MOVES,ScreenText *MOVE_COUNT);

    void set_turn(Sprite* white,Sprite* black);
    void do_events(Event event,int x,int y);

    void Pick_Pieces(Event event,int MX,int MY);
    void Hower_Pieces(Event event,int MX,int MY);
    void Release_Pieces(Event event);

    void do_things_1(int i,int MX,int MY);
    void do_things_2(float nx,float ny);
};

#endif // PLAY_H
