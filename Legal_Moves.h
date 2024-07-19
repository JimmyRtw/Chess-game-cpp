#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


#include <bits/stdc++.h>

#include "Special_Moves.h"
#include "Shapes.h"
#include "Internal_Chess_Board.h"
#include "Piece.h"
#include "ScreenText.h"

using namespace std;
using namespace sf;

#ifndef LEGAL_MOVES_H
#define LEGAL_MOVES_H

class Legal_Moves
{
    private:

    vector<vector<int>>Nums_Square;

    int sliding_direction[8] = {-8,+1,+8,-1,-9,-7,+9,+7};
    int horse_direction[8][2] = {{-1,-2},{1,-2},{-1,2},{1,2},{-2,-1},{2,-1},{-2,1},{2,1}};
    int king_direction[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{-1,1},{1,1},{1,-1}};
    int pawn_direction[4][2] = {{1,-1},{1,1},{1,0},{2,0}};

    vector<int>temp_legal_moves;

    vector<int>All_Enemy_legal_moves;

    stack<pair<string,string>> undo;
    stack<pair<string,string>> redo;

    Special_Moves* sm;

    public:

    Legal_Moves();

    void undo_move(Internal_Chess_Board*icb,Piece*piece,Special_Moves*sm,Shapes* shape,Sounds* sound,bool* white_turn,string* s);
    void redo_move(Internal_Chess_Board*icb,Piece*piece,Special_Moves*sm,Shapes* shape,Sounds* sound,bool* white_turn,string* s);

    void do_empty();

    void push_undo_move(string s1,string s2);

    void Generate_Pseudo_Legal_Moves(float x,float y,char *InternalChessBoard,bool Switch);
    void Generate_All_Legal_Moves(char *InternalChessBoard,bool white_turn,bool Switch);
    void Generate_Sliding_Moves(int curr_pos,char curr_char,char* InternalChessBoard,int start_dir,int end_dir,bool Switch);
    void Generate_Pawn_Moves(int curr_pos,char curr_char,char* InternalChessBoard,bool Switch);
    void Generate_Knight_Moves(int curr_pos,char curr_char,char* InternalChessBoard,bool Switch);
    void Generate_King_Moves(int curr_pos,char curr_char,char* InternalChessBoard,bool Switch);
    string Generate_Move_notation(float ox,float oy,float nx,float ny);

    void check_checkmate(Shapes* shape,Special_Moves* sm,Sprite* E_pieces,Sprite* F_Pieces,ScreenText* Move_Count,bool turn,char* icb);

    void clear_Vector();
    void clear_Enemy();

    void init_Nums_Square();
    void print_Nums_Square();
    void count_Nums_Square();

    void Update_Pseudo_to_Legal(float ox,float oy,Sprite* king,char* icb);
    string updated_fen_string(string Start_Fen,string Move,int spm);
    int is_legal_move(float nx,float ny,float ox,float oy,char icb[],Sprite* Enemy);
    void capture_piece(float nx,float ny,Sprite* Enemy);

    vector<int> return_Enemy();
    vector<int> return_Legal_Move();
};

#endif // LEGAL_MOVES_H
