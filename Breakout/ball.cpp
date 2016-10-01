#include "ball.h"

Ball::Ball(){
	circle.setRadius(ballRadius);
	direction = sf::Vector2f(2, -2);
}
sf::Vector2f Ball::getDirection(){
	return direction;
}
void Ball::setDirection(const sf::Vector2f &dir){
	direction = dir;
}
void Ball::setDirection(const float &x, const float &y){
	direction.x = x;
	direction.y = y;
}
sf::CircleShape Ball::getShape(){
	return circle;
}
void Ball::draw(sf::RenderTarget &target){
	target.draw(circle);
}

void Ball::setPosition(const sf::Vector2f &position){
	circle.setPosition(position);
}

sf::Vector2f Ball::getPosition(){
	return circle.getPosition();
}

unsigned int Ball::getRadius(){
	return ballRadius;
}

void Ball::update(){
	circle.move(direction);
}

void Ball::reset(){
	if(direction.y > 0)
		direction.y *= -1;

	circle.setFillColor(sf::Color::White);
	circle.setPosition(sf::Vector2f(WIDTH/2 - ballRadius, HEIGHT - 45 - 2*ballRadius));
}

void Ball::accelerate(){
	direction.x *= 1.5f;
	direction.y *= 1.5f;
}
