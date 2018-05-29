//
// Created by mateusz on 29.05.18.
//



#pragma once
#include "Game.h"
#include <iostream>
#include <vector>
//sterowanie:
//strza�ki lewo, prawo, g�ra(start)


const int b_wys = 22;
const int b_szer = 66;

const int wys = 600;
const int szer = 800;


//*********************************************************
template <class T1, class T2> bool kolizja(T1 *A, T2 *B)
{
    return A->right() >= B->left() && A->left() <= B->right() && A->down() >= B->top() && A->top() <= B->down();
}

//*********************************************************
bool kolizjaTest(Block* block, Ball* ball, int& liczbaBlokow)
{
    if (!kolizja(block, ball))return false;

    if (!block->get_zbij())
    {

        block->set_zbij();

        liczbaBlokow--;

        ball->neg_y();

    }
    return block->get_zbij();
}






//*********************************************************
Game::Game(void)
{
    state = MENU;
    window = new RenderWindow;


    try {
        if (!font.loadFromFile("../data/Mecha.ttf"))throw(255);
    }

    catch (int &a) {
        state = GAME;
        cout << "\n\nblad ladowania czcionki\n" << endl;
        cout << "START GRY -> ENTER" << endl;
        cout << "COFNIJ -> ESCAPE" << endl;
        cout << "Uzyj strzalek lewo/prawo do poruszania platforma oraz strzalki w gore aby rozpoczac gre\n\n" << endl;

    }

    if (!texture_B.loadFromFile("../data/brick_blue_small.png"))
    {
        //MessageBox(NULL, L"Textures notk found!", L"ERROR", NULL);
        //return;
        texture_B.setSmooth(true);
    }

    if (!texture_G.loadFromFile("../data/brick_green_small.png"))
    {
        /*MessageBox(NULL, L"Textures notk found!", L"ERROR", NULL);
        return;*/
        texture_G.setSmooth(true);
    }

    if (!texture_P.loadFromFile("../data/brick_pink_small.png"))
    {
        //MessageBox(NULL, L"Textures notk found!", L"ERROR", NULL);
        //return;
        texture_P.setSmooth(true);
    }

    if (!texture_R.loadFromFile("../data/brick_red_small.png"))
    {
        //MessageBox(NULL, L"Textures notk found!", L"ERROR", NULL);
        //return;
        texture_R.setSmooth(true);
    }



    try {
        if (!texture1.loadFromFile("../data/background1.jpg")) throw(255);
        tlospr1.setTexture(texture1);

    }
    catch (int &a) {
        RenderTexture texturee;
        if (!texturee.create(szer, wys))
            return;
        tlospr1.setTexture(texturee.getTexture());
        tlospr1.setColor(Color(212, 217, 219));
        tlospr1.setOrigin(0, 0);




    }

    try {
        if (!texture.loadFromFile("../data/background.jpg"))throw(255);
        tlospr.setTexture(texture);

    }
    catch (int &a) {
        RenderTexture texturee;
        if (!texturee.create(szer, wys))
            return;
        tlospr.setTexture(texturee.getTexture());
        tlospr.setColor(Color(212, 217, 219));
        tlospr.setOrigin(0, 0);
    }




    zycie = new int;
    pkt = new int;
    *zycie = 0;
    *pkt = 0;
}

//*********************************************************
Game::~Game(void)
{

    delete zycie;
    delete pkt;
    delete window;
}

//*********************************************************
void Game::pkt_plus() {
    *pkt += 30;
}


//*********************************************************
void Game::runGame()
{


    while (state != END)
    {
        window->create(VideoMode(szer, wys), "GRA");
        switch (state)
        {
            case GameState::MENU:
                menu(window);
                break;
            case GameState::GAME:
                single(window);
                break;
            case GameState::GAME_OVER:
                game_over(window);
                break;
            case GameState::WIN:
                win(window);
                break;
        }
    }
}
//*********************************************************
void Game::update() {

    napis = "    Zycia " + to_string(*zycie) + "    Punkty " + to_string(*pkt);
    text.setString(napis);
    text.setPosition((szer - text.getGlobalBounds().width) / 2, wys - 40);
    text.setFont(font);
    text.setCharacterSize(20);

}
//*********************************************************
void Game::menu(RenderWindow *window)
{

    Text title("Arkanoid", font, 80);
    title.setStyle(Text::Bold);

    title.setPosition(szer / 2 - title.getGlobalBounds().width / 2, 20);
    title.setColor(Color::Black);

    const int ile = 2;

    Text tekst[ile];

    string str[] = { "Play","Exit" };
    for (int i = 0; i<ile; i++)
    {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(65);

        tekst[i].setString(str[i]);

        tekst[i].setPosition(szer / 2.f - tekst[i].getGlobalBounds().width / 2.f, 250.f + i * 120.f);
    }

    while (state == MENU)
    {

        Vector2f mouse(Mouse::getPosition(*window));
        Event event;

        while (window->pollEvent(event))
        {
            // ESC lub przycisk X
            if (event.type == Event::Closed || event.type == Event::KeyPressed &&
                                               event.key.code == Keyboard::Escape)
                state = END;

                // GAME
            else if (tekst[0].getGlobalBounds().contains(mouse) &&
                     event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left || event.type == Event::KeyPressed &&
                                                                                                  event.key.code == Keyboard::Return)
            {
                state = GAME;
            }

                //END
            else if (tekst[1].getGlobalBounds().contains(mouse) &&
                     event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                state = END;
            }
        }
        for (int i = 0; i<ile; i++)
            if (tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setColor(Color::Cyan);
            else tekst[i].setColor(Color::Black);




        window->clear();

        window->draw(tlospr);
        window->draw(title);
        for (int i = 0; i<ile; i++)
            window->draw(tekst[i]);

        window->display();
    }
}






//*********************************************************
void Game::single(RenderWindow *window)
{
    window->setMouseCursorVisible(false);
    window->clear();



    *pkt = 0;
    *zycie = 3;

    ball = new Ball(szer / 2-10, wys - 80);
    paddle = new Paddle((szer / 2)-10, wys - 60);
    window->setFramerateLimit(60);

    vector<Block *> blocks;


    int liczbaBlokow = 0;
    unsigned int l_kolumny = (szer - 20) / (b_szer + 10);//liczba blok�w w rzedzie
    l_kolumny--;



    unsigned int  l_rzad = 4;


    for (unsigned int i = 0; i < l_rzad; i++)
    {
        for (unsigned int j = 0; j < l_kolumny; j++)
        {



            switch (i)
            {
                case 0:
                case 4:
                    blocks.push_back(new Block(float((j + 1)*(b_szer + 13)), float((i + 2)*(b_wys + 5)), float(b_szer), float(b_wys), texture_R));
                    break;
                case 1 :
                case 5 :
                    blocks.push_back(new Block(float((j + 1)*(b_szer + 13)), float((i + 2)*(b_wys + 5)), float(b_szer), float(b_wys), texture_B));
                    break;
                case 2:
                case 6:
                    blocks.push_back(new Block(float((j + 1)*(b_szer + 13)), float((i + 2)*(b_wys + 5)), float(b_szer), float(b_wys), texture_G));
                    break;
                default:
                    blocks.push_back(new Block(float((j + 1)*(b_szer + 13)), float((i + 2)*(b_wys + 5)), float(b_szer), float(b_wys), texture_P));

                    break;
            }
            liczbaBlokow++;

        }
    }




    //glowna petla GRY

    while (state == GAME)
    {
        Event event;

        while (window->pollEvent(event))
        {
            // ESC lub przycisk X
            if (event.type == Event::Closed || event.type == Event::KeyPressed &&
                                               event.key.code == Keyboard::Escape)
                state = MENU;
            //pauza
            if (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Space)
            {
                state = PAUSE;

                Text title("PAUSE", font, 80);
                title.setStyle(Text::Bold);

                title.setPosition(szer / 2 - title.getGlobalBounds().width / 2, wys / 2 + 50);
                title.setColor(Color::Black);
                window->draw(title);
                window->display();

                while (state == PAUSE) {
                    Event event1;
                    while (window->pollEvent(event1))
                        if (event1.type == Event::KeyPressed &&
                            event1.key.code == Keyboard::Space)
                            state = GAME;

                }

            }
        }
        //GRA
        window->clear(Color::Black);


        ball->update();
        paddle->update();
        update();


        window->draw(tlospr);
        window->draw(*ball);
        window->draw(*paddle);
        window->draw(text);


        for (vector<Block *>::iterator it = blocks.begin(); it != blocks.end(); it++) {

            if (!(*it)->get_zbij())
            {
                if (kolizjaTest((*it), ball, liczbaBlokow))
                {
                    pkt_plus();
                    break;
                }

            }

        }


        for (vector<Block *>::iterator it = blocks.begin(); it != blocks.end(); it++) {

            if (!(*it)->get_zbij())
            {
                window->draw(*(*it));
            }

        }




        window->display();




        if ((ball->left() + ball->get_Pro() >= paddle->left()) && (ball->left() <= paddle->right())
            && (ball->top() + (2 * ball->get_Pro()) >= paddle->top()) && (ball->top() <= paddle->top())) {

            ball->neg_y();

        }

        else if (ball->top() >= paddle->top() + 5)
        {
            *zycie = *zycie - 1;;
            *pkt -= 50;

            //koniec gry
            while (*zycie <= 0 && state == GAME) {

                state = GAME_OVER;

            }

            ball->set_pred(0);
            ball->set_poz(szer / 2, wys - 80);
            paddle->set_poz(szer / 2, wys - 60);


        }

        if (liczbaBlokow == 0) {
            state = WIN;
            liczbaBlokow++;
            //system("pause");
        }

    }


    for (vector<Block* >::iterator it = blocks.begin(); it != blocks.end(); it++)
        delete (*it);

    delete ball;
    delete paddle;
    blocks.clear();
    //delete blocks;
}

//*************************************************************************************************
void Game::game_over(RenderWindow *window) {
    window->setMouseCursorVisible(true);



    while (state == GAME_OVER) {
        Text title(L"KONIEC GRY PORAZKA", font, 80);

        title.setStyle(Text::Bold);
        title.setPosition(szer / 2 - title.getGlobalBounds().width / 2, 60);


        const int ile = 2;
        Text tekst[ile];
        string str[] = { "OK (ESCAPE)","Jeszcze raz(ENTER)" };
        for (int i = 0; i<ile; i++)
        {
            tekst[i].setFont(font);
            tekst[i].setCharacterSize(65);

            tekst[i].setString(str[i]);

            tekst[i].setPosition(szer / 2.f - tekst[i].getGlobalBounds().width / 2.f, 250.f + i * 120.f);
        }





        Vector2f mouse(Mouse::getPosition(*window));


        Event event;

        while (window->pollEvent(event))
        {
            // ESC lub przycisk X
            if (event.type == Event::Closed || event.type == Event::KeyPressed &&
                                               event.key.code == Keyboard::Escape)
                state = MENU;

            //Koniec
            if (tekst[0].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                state = MENU;


            }

            //jeszcze raz
            if (tekst[1].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left || event.type == Event::KeyPressed &&
                                                                                             event.key.code == Keyboard::Return)
            {
                state = GAME;


            }

        }

        for (int i = 0; i<ile; i++)
            if (tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setColor(Color::Cyan);
            else tekst[i].setColor(Color::Black);

        update();
        window->clear();
        window->draw(tlospr1);
        window->draw(title);
        window->draw(text);
        window->draw(tekst[0]);
        window->draw(tekst[1]);
        window->display();
    }
}

//*********************************************************
void Game::win(RenderWindow *window) {

    window->setMouseCursorVisible(true);




    Text title("WYGRANA", font, 80);

    title.setStyle(Text::Bold);
    title.setPosition(szer / 2 - title.getGlobalBounds().width / 2, 60);


    const int ile = 2;
    Text tekst[ile];
    string str[] = { "OK (ESCAPE)","Jeszcze raz(ENTER)" };
    for (int i = 0; i<ile; i++)
    {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(65);

        tekst[i].setString(str[i]);

        tekst[i].setPosition(szer / 2.f - tekst[i].getGlobalBounds().width / 2.f, 250.f + i * 120.f);
    }

    while (state == WIN) {
        Vector2f mouse(Mouse::getPosition(*window));

        Event event;

        while (window->pollEvent(event))
        {
            // ESC lub przycisk X
            if (event.type == Event::Closed || event.type == Event::KeyPressed &&
                                               event.key.code == Keyboard::Escape)
                state = MENU;



            //koniec
            if (tekst[0].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                state = MENU;


            }

            //jeszcze raz
            if (tekst[1].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left || event.type == Event::KeyPressed &&
                                                                                             event.key.code == Keyboard::Return)
            {
                state = GAME;


            }

        }

        for (int i = 0; i<ile; i++)
            if (tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setColor(Color::Cyan);
            else tekst[i].setColor(Color::Black);

        update();
        window->clear();
        window->draw(tlospr);
        window->draw(title);
        window->draw(text);
        window->draw(tekst[0]);
        window->draw(tekst[1]);
        window->display();
    }
}



