#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Sound.h"

using namespace std;
using namespace sf;

#ifndef SPECIAL_MOVES_H
#define SPECIAL_MOVES_H

class Special_Moves
{
    private:

    public:

    Special_Moves();

    void init_special_moves(string Start_Fen,bool* white_turn);

    void false_castle(bool Turn,int n);

    bool can_castle_qs(vector<int>invalid,int curr_pos,char curr_char,char* icb);
    bool can_castle_ks(vector<int>invalid,int curr_pos,char curr_char,char* icb);

    int is_checkmate(int x,vector<int>moves);
    int is_check(Sprite* king,vector<int>invalid);

    int set_passent(float ox,float oy,float nx,float ny,char* icb,Sprite* Enemy);
    int can_passent(int ox,int oy,char* icb);

    void En_passent();
    int Castle(float ox,float oy,float nx,float ny,char* icb,Sprite* pieces);
    vector<bool> castling_permissions();

    char promote(Sprite*pieces,char* icb,int MX,int MY,int n,bool *white_turn);
    bool set_promotion(Sprite*pieces,float nx,float ny,char* icb,int n,int Move,Sounds *sound);

    void Announce_Winner(Sprite* pawn,int Move);
};

#endif // SPECIAL_MOVES_H
