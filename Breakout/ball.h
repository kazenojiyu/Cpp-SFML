#include <SFML/Graphics.hpp>
#include "config.h"

#ifndef BALL_H
#define BALL_H

class Ball{
private:
	sf::CircleShape circle;
	unsigned int ballRadius = 5;
	sf::Vector2f direction;
public:
	Ball();
	sf::Vector2f getDirection();
	void setDirection(const sf::Vector2f &dir);
	void setDirection(const float &x, const float &y);
	sf::CircleShape getShape();
	void draw(sf::RenderTarget &target);
	void setPosition(const sf::Vector2f &position);
	sf::Vector2f getPosition();
	unsigned int getRadius();
	void update();
	void reset();
	void accelerate();
};

#endif
