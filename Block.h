//
// Created by mateusz on 29.05.18.
//

#ifndef TEST_BLOCK_H
#define TEST_BLOCK_H

#include <SFML/Graphics.hpp>
//#include <windows.h>
using namespace sf;


class Block :
        public Drawable
{
public:
    Block(float X, float Y, float szer, float wys, Texture &texture);
    ~Block() {}



    float left();
    float right();
    float top();
    float down();

    bool get_zbij();
    void set_zbij();
    //Vector2f get_Size();
    virtual void draw(RenderTarget& target, RenderStates state) const;


private:
    RectangleShape blok;
    //Texture texture;
    //Sprite blok;
    bool visible = false;
};



#endif //TEST_BLOCK_H
