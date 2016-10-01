#include "missile.h"

Missile::Missile(const sf::Vector2f &pos){
  shape.setSize(sf::Vector2f(3,10));
  shape.setPosition(pos);
  shape.setFillColor(sf::Color::White);
}

void Missile::setDirection(const int &x, const int &y){
  direction.x = x;
  direction.y = y;
}

sf::Vector2f Missile::getPosition(){
  return shape.getPosition();
}

void Missile::draw(sf::RenderTarget &target){
  target.draw(shape);
}

void Missile::update(){
  shape.move(direction);
}

sf::FloatRect Missile::getGlobalBounds(){
  return shape.getGlobalBounds();
}

void Missile::clear(){
  shape.setFillColor(sf::Color::Black);
  direction.x = 0;
  direction.y = 0;
  shape.setPosition(0,0);
}
