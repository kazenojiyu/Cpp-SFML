#include "paddle.h"

Paddle::Paddle(){
  width = 50;
  height = 20;

  shape.setPosition(WIDTH/2 - width/2, HEIGHT - height - 5);
  shape.setTextureRect(sf::IntRect(0, 0, width, height));
  shape.setColor(sf::Color(0,255,0));
}

void Paddle::draw(sf::RenderTarget &target){
  target.draw(shape);
}
sf::Vector2f Paddle::getPosition(){
  return shape.getPosition();
}
sf::Vector2f Paddle::getSize(){
  return sf::Vector2f(width, height);
}

void Paddle::update(){
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && getPosition().x >= 1)
    shape.move(-5, 0);
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && getPosition().x + width <= WIDTH - 1)
    shape.move(+5, 0);
}

void Paddle::setTexture(const sf::Texture &texture){
  shape.setTexture(texture);
}
