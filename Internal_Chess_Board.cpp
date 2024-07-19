#include "Internal_Chess_Board.h"

Internal_Chess_Board::Internal_Chess_Board()
{
    Set_Initial_Internal_chess_board(piece.Start_Fen_string());
}

void Internal_Chess_Board :: Set_Initial_Internal_chess_board(string Start_Fen)
{
    int row = 0;
    int col = 0;

    for(int i=0; i<64 ; i++)
    {
        Icb[i] = 'O';
    }

    for(int i=0; i<Start_Fen.size(); i++)
    {
        if(Start_Fen[i] == '/')
        {
            row += 1;
            col = 0;
        }
        else if((Start_Fen[i]>='A' && Start_Fen[i]<='Z')||((Start_Fen[i]>='a' && Start_Fen[i]<='z')))
        {
            Icb[row*8+col] = Start_Fen[i];
            col += 1;
        }
        else if(Start_Fen[i]==' ')
        {
            break;
        }
        else
        {
            col += 1*(((Start_Fen[i])-'0'));
        }

    }
}

void Internal_Chess_Board :: Update_Internal_chess_board(int nx,int ny,int ox,int oy)
{
        int destcolour,curcolour;

        int i = (nx-575)/110;
        int j = (ny-155)/110;

        int k = (ox-575)/110;
        int l = (oy-155)/110;

        char destination = Icb[j*8+i];
        char curlocation = Icb[l*8+k];

        if((int(curlocation)>=65)&&(int(curlocation)<=90))
        {
            curcolour = 1;
        }
        if((int(curlocation)>=97)&&(int(curlocation)<=122))
        {
            curcolour = 2;
        }

        if((int(destination)>=65)&&(int(destination)<=90))
        {
            destcolour = 1;
        }
        if((int(destination)>=97)&&(int(destination)<=122))
        {
            destcolour = 2;
        }

        if(destination=='O')
        {
            Icb[j*8+i]=curlocation;
            Icb[l*8+k]='O';
        }

        if(destination!='O')
        {
            if(destcolour==curcolour)
            {
                Icb[j*8+i]=destination;
                Icb[l*8+k]=curlocation;

            }
            if(destcolour!=curcolour)
            {
                Icb[j*8+i]=curlocation;
                Icb[l*8+k]='O';
            }
        }
       //Print_Internal_chess_board();
}



void Internal_Chess_Board :: Print_Internal_chess_board()
{
    system("cls");

    for(int i=0;i<64;i++)
    {
        if(i%8==0)
        {
            cout<<endl;
        }

        cout<<Icb[i]<<" ";
    }

    cout<<"\n\n";

}

char* Internal_Chess_Board :: InternalChessBoard()
{
    return Icb;
}
