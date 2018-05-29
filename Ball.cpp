//
// Created by mateusz on 29.05.18.
//

#include "Ball.h"
//#include "stdafx.h"
//#include "Ball.h"
//#include <Windows.h>
const int b_wys = 22;
const int b_szer = 66;

const int wys = 600;
const int szer = 800;

Ball::Ball(float x, float y)
{

    try {
        if (!texture.loadFromFile("../data/pilka.png"))throw(255);
        pilka.setTexture(&texture);

    }
    catch (int &a) {

        pilka.setFillColor(Color(0, a, 0));
    }

    pilka.setPosition(x, y);
    pilka.setRadius(this->ballPromien);
    pilka.setOrigin(this->ballPromien, this->ballPromien);

    state = START;


}


void Ball::draw(RenderTarget& target, RenderStates state)const
{
    target.draw(this->pilka, state);
}


void Ball::update() {

    if (state == START) {
        predkosc.x = 0;
        float x{ 8.f };

        if (Keyboard::isKeyPressed(Keyboard::Left) && this->left() > 0 + 60)
        {
            predkosc.x = -x;
        }

        else if (Keyboard::isKeyPressed(Keyboard::Right) && this->right() < szer - 60)
        {
            predkosc.x = x;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) && state == START)
    {

        set_pred(6);
        state = INGAME;
    }

    pilka.move(this->predkosc);

    if (this->left() < 0)
    {
        neg_x();
    }

    if (this->right() > szer)
    {
        neg_x();
    }


    if (this->top() < 0)
    {

        neg_y();
    }

    if (this->down() > wys) //test
    {

        neg_y();
    }

}




float Ball::left() {

    return this->pilka.getPosition().x - pilka.getRadius();
}

float Ball::right() {
    return this->pilka.getPosition().x + pilka.getRadius();
}

float Ball::top() {
    return this->pilka.getPosition().y - pilka.getRadius();
}

float Ball::down() {
    return this->pilka.getPosition().y + pilka.getRadius();
}


void Ball::neg_y() { predkosc.y = -predkosc.y; }
void Ball::neg_x() { predkosc.x = -predkosc.x; }
float Ball::get_Pro() { return ballPromien; }
void Ball::set_pred(float x) {

    ballPredkosc = x;
    predkosc = { ballPredkosc ,-ballPredkosc };
    if (state == START) state = INGAME;
    if (state == INGAME) state = START;

}

void Ball::set_poz(float t_x, float t_y) { pilka.setPosition(t_x, t_y); }
