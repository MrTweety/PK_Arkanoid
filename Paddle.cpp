//
// Created by mateusz on 29.05.18.
//

//#include "stdafx.h"
#include "Paddle.h"
//#include<Windows.h>
const int b_wys = 22;
const int b_szer = 66;

const int wys = 600;
const int szer = 800;

Paddle::Paddle(float X, float Y)
{



    try {
        if (!texture.loadFromFile("../data/platforma.png"))throw(255);
        paletka.setTexture(&texture);

    }
    catch (int &a) {

        paletka.setFillColor(Color(a, a, 0));
    }

    paletka.setPosition(X, Y);
    paletka.setTexture(&texture);

    paletka.setSize({ this->paddleSzer,this->paddleWys });
    paletka.setOrigin(paddleSzer / 2.f, paddleWys / 2.f);
}


void Paddle::draw(RenderTarget& target, RenderStates state)const
{
    target.draw(this->paletka, state);
}


void Paddle::update()
{
    paletka.move(this->predkosc);
    predkosc.x = 0;

    if (Keyboard::isKeyPressed(Keyboard::Left) && this->left() > 0)
    {
        predkosc.x = -paddlePredkosc;
    }

    else if (Keyboard::isKeyPressed(Keyboard::Right) && this->right() < szer)
    {
        predkosc.x = paddlePredkosc;
    }

}



float Paddle::left() {
    return this->paletka.getPosition().x - paletka.getSize().x / 2.f;
}

float Paddle::right() {
    return this->paletka.getPosition().x + paletka.getSize().x / 2.f;
}

float Paddle::top() {
    return this->paletka.getPosition().y - paletka.getSize().y / 2.f;
}

float Paddle::down() {
    return this->paletka.getPosition().y + paletka.getSize().y / 2.f;
}


float Paddle::get_wys() { return paddleWys; }
float Paddle::get_szer() { return paddleSzer; }
void Paddle::set_poz(float t_x, float t_y) { paletka.setPosition(t_x, t_y); }

