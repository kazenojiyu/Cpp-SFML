#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "config.h"

#ifndef SNAKE_ELEMENT_H
#define SNAKE_ELEMENT_H

class Snake_element{
private:
    sf::RectangleShape rectangle;
    bool is_head;    
public:    
    Snake_element();
    Snake_element(const bool &head);

    void draw(sf::RenderTarget &target);

    sf::RectangleShape getShape();

    void setPosition(const sf::Vector2f &pos);
    void setPosition(const unsigned int &x, const unsigned int &y);
    sf::Vector2f getPosition();

    void move(const sf::Vector2f &dir);

};

#endif