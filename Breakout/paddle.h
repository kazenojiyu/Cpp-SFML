#include <SFML/Graphics.hpp>
#include "config.h"

#ifndef PADDLE_H
#define PADDLE_H

class Paddle{
private:
	unsigned int speed;
	sf::RectangleShape rectangle;

public:
	Paddle();
	void draw(sf::RenderTarget &target);
	void setSpeed(const unsigned int &speed_p);
	unsigned int getSpeed();
	void setPosition(const sf::Vector2f &position);
	void setPosition(const float &x, const float &y);
	sf::Vector2f getPosition();
	void setSize(const sf::Vector2f &size);
	sf::Vector2f getSize();
	sf::RectangleShape getShape();
	void update();
	void reset();
};

#endif
