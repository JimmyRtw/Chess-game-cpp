#include "Button.h"

void Button::button_font()
{
    font.loadFromFile(common_path+"RedHatDisplay-Black.otf");
}

void Button::button_text()
{
    text.setFont(font);
    text.setString(Name);
    text.setCharacterSize(24);

    text.setOrigin(65,15);
    text.setFillColor(Color::White);
}

void Button::button_texture()
{
    Button_n_tex.loadFromFile(common_path+"button_n.png");
    Button_h_tex.loadFromFile(common_path+"button_h.png");
    Button_bg_tex.loadFromFile(common_path+"buttonbg.png");
}

void Button::button_sprite()
{
    Button_n_spr.setTexture(Button_n_tex);
    Button_h_spr.setTexture(Button_h_tex);
    Button_bg_spr.setTexture(Button_bg_tex);

    Button_n_spr.setOrigin(100,30);
    Button_h_spr.setOrigin(100,30);
    Button_bg_spr.setOrigin(105,35);
}

void Button::button_setPosition()
{
    Button_n_spr.setPosition(X,Y);
    Button_h_spr.setPosition(X,Y);
    Button_bg_spr.setPosition(X,Y);
    text.setPosition(X,Y);
}

void Button::init_button()
{
    button_texture();
    button_sprite();
    button_font();
    button_text();
    button_setPosition();
}

void Button::hower_over_button(int x,int y)
{
    if(Button_n_spr.getGlobalBounds().contains(x,y))
    {
        Button_h_spr.setPosition(X,Y);
    }
    else
    {
        Button_h_spr.setPosition(-500,-500);
    }
}

bool Button::is_button_clicked(int x,int y,Event event)
{
    if((event.type==Event::MouseButtonPressed)&&(event.key.code==Mouse::Left))
    {
       if(Button_h_spr.getGlobalBounds().contains(x,y))
        {
            return true;
        }
    }
    return false;
}

void Button::draw_button(RenderWindow* window)
{
    window->draw(Button_bg_spr);
    window->draw(Button_h_spr);
    window->draw(Button_n_spr);
    window->draw(text);
}
