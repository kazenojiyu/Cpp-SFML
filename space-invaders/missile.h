#include <SFML/Graphics.hpp>
#include "config.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile{
private:
  sf::RectangleShape shape;
  sf::Vector2f direction;
public:
  Missile(const sf::Vector2f &pos);
  void setDirection(const int &x, const int &y);
  sf::Vector2f getPosition();
  void draw(sf::RenderTarget &target);
  void update();
  sf::FloatRect getGlobalBounds();
  void clear();
};

#endif
