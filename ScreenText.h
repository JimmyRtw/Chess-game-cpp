#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

#ifndef SCREENTEXT_H
#define SCREENTEXT_H

class ScreenText
{
    private:

    Font font;
    Text text;

    Color colour;

    int Size;

    float x,y,ox,oy;

    string common_path = "./IMAGES/SCREEN_TEXT/";
    string name;

    public:

    ScreenText(Color colour,float x,float y,float ox,float oy,string name,int Size)
    {
        this->name = name;
        this->x = x;
        this->y = y;
        this->colour = colour;
        this->Size = Size;
        this->ox = ox;
        this->oy = oy;

        init_screen_text();
    }

    void init_screen_text();

    void screen_text_font();
    void screen_text_text();
    void screen_text_setPosition();

    void screen_text_change_text(string new_text);
    void draw_screen_text(RenderWindow* window);

};

#endif // SCREENTEXT_H
