#include "alien.h"

Alien::Alien(const int &type){
  type_i = type;
  shape.setSize(sf::Vector2f(20,20));
  shape.setFillColor(sf::Color::Red);
  life = 1;
}

sf::Vector2f Alien::getPosition(){
  return shape.getPosition();
}

void Alien::setPosition(const float &x, const float &y){
  shape.setPosition(x, y);
}

sf::Vector2f Alien::getSize(){
  return shape.getSize();
}

void Alien::draw(sf::RenderTarget &target){
  target.draw(shape);
}

void Alien::move(const float &x, const float &y){
  shape.move(x, y);
}

sf::FloatRect Alien::getGlobalBounds(){
  return shape.getGlobalBounds();
}
