#include "ScreenText.h"

void ScreenText::init_screen_text()
{
    screen_text_font();
    screen_text_text();
    screen_text_setPosition();
}

void ScreenText::screen_text_font()
{
    font.loadFromFile(common_path+"RedHatText-Regular.otf");
}

void ScreenText::screen_text_text()
{
    text.setFont(font);
    text.setString(name);
    text.setCharacterSize(Size);

    text.setOrigin(this->ox,this->oy);
    text.setFillColor(this->colour);
}

void ScreenText::screen_text_setPosition()
{
    text.setPosition(this->x,this->y);
}

void ScreenText::screen_text_change_text(string new_text)
{
    text.setString(new_text);
}

void ScreenText::draw_screen_text(RenderWindow* window)
{
    window->draw(text);
}
