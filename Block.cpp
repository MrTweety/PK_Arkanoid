//
// Created by mateusz on 29.05.18.
//

#include "Block.h"
//#include "stdafx.h"
//#include "Block.h"



Block::Block(float X, float Y, float szer, float wys, Texture &texture)
{

    blok.setPosition(X, Y);
    blok.setSize({ szer,wys });
    blok.setOrigin(szer / 2.f, wys / 2.f);


    try {
        if (texture.isSmooth()) {

            throw(255);
        };
        blok.setTexture(&texture);
    }


    catch (int &a) {
        int l_1 = rand() % 255;
        int l_2 = rand() % 255;
        int l_3 = rand() % 255;
        blok.setFillColor(Color(l_1, l_2, l_3));
    }



}




void Block::draw(RenderTarget& target, RenderStates state)const
{
    target.draw(this->blok, state);
}





float Block::left() {

    return this->blok.getPosition().x - blok.getSize().x / 2.f;
    //return this->blok.getPosition().x - get_Size().y / 2.f;
}

float Block::right() {

    return this->blok.getPosition().x + blok.getSize().x / 2.f;
    //return this->blok.getPosition().x + get_Size().y / 2.f;
}

float Block::top() {

    return this->blok.getPosition().y - blok.getSize().y / 2.f;
    //return this->blok.getPosition().y - get_Size().y / 2.f;
}

float Block::down() {

    return this->blok.getPosition().y + blok.getSize().y / 2.f;
    //return this->blok.getPosition().y + get_Size().y / 2.f;
}



bool Block::get_zbij()
{
    return this->visible;
}

void Block::set_zbij()
{
    this->visible = true;

}

/*
Vector2f Block::get_Size()
{

return{ blok.getGlobalBounds().width, blok.getGlobalBounds().height };
}
*/