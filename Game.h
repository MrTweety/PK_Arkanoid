//
// Created by mateusz on 29.05.18.
//

#ifndef TEST_GAME_H
#define TEST_GAME_H



#include <SFML/Graphics.hpp>
//#include <Windows.h>
#include <string>
#include "Ball.h"
#include"Paddle.h"
#include"Block.h"




using namespace std;
using namespace sf;

class Game

{
public:
    Game(void);
    ~Game(void);

    void runGame();
    void update();
    void pkt_plus();





protected:
    enum GameState {
        MENU, GAME, GAME_OVER, END, WIN, PAUSE
    };
    GameState state;

private:
    Font font;

    int *zycie = NULL;
    int *pkt = NULL;

    Texture texture;
    Texture texture1;
    Texture texture_B;
    Texture texture_G;
    Texture texture_P;
    Texture texture_R;
    Sprite tlospr;
    Sprite tlospr1;
    String napis;
    Text text;

    RenderWindow *window;



    Ball *ball;
    Paddle *paddle;



    void menu(RenderWindow *window);
    void single(RenderWindow *window);
    void game_over(RenderWindow *window);
    void win(RenderWindow *window);

};


#endif //TEST_GAME_H
