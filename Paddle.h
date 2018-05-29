//
// Created by mateusz on 29.05.18.
//

#ifndef TEST_PADDLE_H
#define TEST_PADDLE_H




#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;



class Paddle : public Drawable
{
public:
    Paddle(float X, float Y);
    ~Paddle() {}

    void update();

    float left();
    float right();
    float top();
    float down();


    float get_wys();
    float get_szer();
    void set_poz(float t_x, float t_y);
    virtual void draw(RenderTarget& target, RenderStates state) const;

private:
    RectangleShape paletka;
    Texture texture;



    const float paddlePredkosc = 8.0f;
    Vector2f predkosc = Vector2f(paddlePredkosc, 0.f);
    const float paddleSzer = 120.0f;
    const float paddleWys = 20.0f;

};


#endif //TEST_PADDLE_H
