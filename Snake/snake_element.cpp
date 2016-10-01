#include "snake_element.h"

Snake_element::Snake_element(){}
Snake_element::Snake_element(const bool &head){
    is_head = head;
    
    rectangle.setSize(sf::Vector2f(ELEMENT_SIZE - 1, ELEMENT_SIZE - 1));
    rectangle.setOutlineThickness(0.5f);
    rectangle.setOutlineColor(sf::Color::Black);
    if(is_head){
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(WIDTH/2, HEIGHT/2);
    }else{
        rectangle.setFillColor(sf::Color::Yellow);
        rectangle.setPosition(-ELEMENT_SIZE, -ELEMENT_SIZE);
    }
}

/**
 * Draw element in the display
 */
void Snake_element::draw(sf::RenderTarget &target){
    target.draw(rectangle);
}

/**
 * Set element position with a Vector2f
 */
void Snake_element::setPosition(const sf::Vector2f &pos){
    rectangle.setPosition(pos);
}

/**
 * Set element position with two integer
 */
void Snake_element::setPosition(const unsigned int &x, const unsigned int &y){
    rectangle.setPosition(x, y);
}

/**
 * Get element position
 */
sf::Vector2f Snake_element::getPosition(){
    return rectangle.getPosition();
}

/**
 * Get snake shape
 */
sf::RectangleShape Snake_element::getShape(){
    return rectangle;
}

/**
 * Move snake element
 */
void Snake_element::move(const sf::Vector2f &dir){
    rectangle.move(dir);
}