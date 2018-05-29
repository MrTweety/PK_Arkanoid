//
// Created by mateusz on 29.05.18.
//

#ifndef TEST_BALL_H
#define TEST_BALL_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
using namespace sf;

class Ball : public sf::Drawable
{
public:
    Ball(float x, float y);
    ~Ball() {}



    enum GameState { START, INGAME };
    GameState state;


    void update();

    float left();
    float right();
    float top();
    float down();


    void neg_y();
    void neg_x();
    void set_pred(float X);
    void set_poz(float t_x, float t_y);


    float get_Pro();

    virtual void draw(RenderTarget& target, RenderStates state) const;



private:

    CircleShape pilka;
    sf::Texture texture;
    const float ballPromien = 12.0f;
    float ballPredkosc = 0.0f;
    Vector2f predkosc = { ballPredkosc, ballPredkosc };



};




#endif //TEST_BALL_H
