#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

#ifndef BUTTON_H
#define BUTTON_H

class Button
{
    private:

    Texture Button_n_tex,Button_h_tex,Button_bg_tex;
    Sprite Button_n_spr,Button_h_spr,Button_bg_spr;

    float X,Y;

    Font font;
    Text text;

    string common_path = "./IMAGES/BUTTON/";
    string Name;

    public:

    Button(string name,float x,float y)
    {
        Name = name;
        X = x;
        Y = y;

        init_button();
    }

    void init_button();

    void button_texture();
    void button_sprite();

    void button_font();
    void button_text();
    void hower_over_button(int x,int y);
    void button_setPosition();

    void draw_button(RenderWindow* window);

    bool is_button_clicked(int x,int y,Event e);
};

#endif // BUTTON_H
