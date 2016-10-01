#include <SFML/Graphics.hpp>
#include "config.h"

#ifndef ALIEN_H
#define ALIEN_H

class Alien{
private:
  sf::RectangleShape shape;
  unsigned int type_i;
  unsigned int life;
public:
  Alien(const int &type);
  sf::Vector2f getPosition();
  void setPosition(const float &x, const float &y);
  sf::Vector2f getSize();
  void draw(sf::RenderTarget &target);
  void move(const float &x, const float &y);
  sf::FloatRect getGlobalBounds();
};

#endif
