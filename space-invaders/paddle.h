#include <SFML/Graphics.hpp>
#include "config.h"

#ifndef PADDLE_H
#define PADDLE_H

class Paddle{
private:
  sf::Sprite shape;
  unsigned int width;
  unsigned int height;

public:
  Paddle();
  void draw(sf::RenderTarget &target);
  void update();
  sf::Vector2f getPosition();
  sf::Vector2f getSize();
  void setTexture(const sf::Texture &texture);
};

#endif
