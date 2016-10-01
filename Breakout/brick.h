#include <SFML/Graphics.hpp>
#include "config.h"

#ifndef BRICK_H
#define BRICK_H

class Brick{

private:
	unsigned int armor;
	unsigned int points;
	unsigned int color_i; // color number (1 = yellow, 2 = green, 3 = orange, 4 = red)
	sf::RectangleShape rectangle;
	std::vector<sf::Color> color_per_line = {sf::Color::Black, sf::Color::Yellow, sf::Color::Green, sf::Color(255,125,0), sf::Color::Red};

public:
	Brick(const unsigned int &armor_p, const unsigned int &points_p, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color, const unsigned int &col);
	sf::RectangleShape getShape();
	void draw(sf::RenderTarget &target);
	unsigned int getArmor();
	unsigned int getPoints();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	unsigned int decrementArmor();
};

#endif
