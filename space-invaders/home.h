#include <SFML/Graphics.hpp>
#include "config.h"
#include "missile.h"

#ifndef HOME_H
#define HOME_H

class Home{
private:
  sf::Texture texture;

  sf::Sprite topLeft_sprite;
  sf::Sprite topRight_sprite;
  sf::Sprite bottomLeft_sprite;
  sf::Sprite bottomRight_sprite;

  unsigned int topLeft_armor;
  unsigned int topRight_armor;
  unsigned int bottomLeft_armor;
  unsigned int bottomRight_armor;

  unsigned int width_element;
  unsigned int height_element;

  sf::Vector2f position;
public:
  Home();
  void setTexture(const sf::Texture &texture);
  void draw(sf::RenderTarget &target);
  void setPosition(const int &x, const int &y);
  sf::Vector2f getSize();
  void checkCollision(std::vector<Missile*> missileInProgress);

private:
  void update_sprite(sf::Sprite* sprite, const unsigned int &armor);
};

#endif
