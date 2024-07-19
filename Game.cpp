#include "Game.h"

Button restart("Start Again",575+110*10,140),Quite_Game("Quit Game",575+110*10,230);

ScreenText Last_Move(Color::Magenta,575+110*9,540,65,15,"Last Move :",33),Move(Color::Magenta,575+110*10.7,540,65,15,"-",33);
ScreenText Legal_moves(Color::Red,575+110*9,590,65,15,"Legal Moves :",33),Move_Count(Color::Red,575+110*11,590,65,15,"-",33);

Game::Game()
{
    init_window();
    Game_loop();
}

void Game::Play_game()
{
    play.Game(piece.white_pieces(),piece.black_pieces(),MX,MY,event,&shape,&icb,&piece,&lm,&sound,&restart,&Quite_Game,&Last_Move,&Move,&Legal_moves,&Move_Count);
}

void Game::Quit_game()
{
    if(event.type == Event::Closed)
    {
        window->close();
    }

    if ((event.type == sf::Event::KeyPressed)&&(event.key.code == Keyboard::Escape))
    {
        window->close();
    }
}

void Game::init_window()
{
    window = new RenderWindow(VideoMode(1920,1080),"Chess",Style::Fullscreen);
    window->setFramerateLimit(120);
}

void Game::Game_loop()
{
    while(window->isOpen())
    {
        update();
    }
}

void Game::update()
{
    while(window->pollEvent(event))
    {

        MX = Mouse::getPosition(*window).x;
        MY = Mouse::getPosition(*window).y;

        Play_game();
        Quit_game();
    }

    draw();
    window->display();
    window->clear();
}

void Game::draw()
{
    board.draw_board(window);
    shape.draw_shapes(window);
    piece.draw_piece(window);
    restart.draw_button(window);
    Quite_Game.draw_button(window);
    Last_Move.draw_screen_text(window);
    Move.draw_screen_text(window);
    Legal_moves.draw_screen_text(window);
    Move_Count.draw_screen_text(window);
}
