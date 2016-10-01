#include <SFML/Graphics.hpp>
#include <vector>
#include "snake_element.h"
#include "config.h"

#ifndef SNAKE_H
#define SNAKE_H

class Snake{
private:
    sf::Vector2f direction_vector;
    std::vector<Snake_element> list;
    int direction;
    unsigned int speed;
    unsigned int cptTicks;
    unsigned int maxSpeed;

public:
    Snake();
    void draw(sf::RenderTarget &target);
    void addElement(const bool &head);
    void update();
    int getSize();
    sf::Vector2f getHeadPosition();    
    bool intersects(const sf::RectangleShape &rect);
    bool eatingItsOwnTail();
    void reset();
private:    
    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();
    void move();
};

#endif