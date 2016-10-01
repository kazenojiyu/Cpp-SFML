#include "paddle.h"

Paddle::Paddle(){
	rectangle.setFillColor(sf::Color(200,200,200));
	speed = 10;
}

void Paddle::draw(sf::RenderTarget &target){
	target.draw(rectangle);
}

void Paddle::setSpeed(const unsigned int &speed_p){
	speed = speed_p;
}
unsigned int Paddle::getSpeed(){
	return speed;
}
void Paddle::setPosition(const sf::Vector2f &position){
	rectangle.setPosition(position);
}
void Paddle::setPosition(const float &x, const float &y){
	rectangle.setPosition(x, y);
}
sf::Vector2f Paddle::getPosition(){
	return rectangle.getPosition();
}

void Paddle::setSize(const sf::Vector2f &size){
	rectangle.setSize(size);
}
sf::Vector2f Paddle::getSize(){
	return rectangle.getSize();
}

sf::RectangleShape Paddle::getShape(){
	return rectangle;
}
void Paddle::update(){
}

void Paddle::reset(){
	rectangle.setFillColor(sf::Color(200,200,200));
	rectangle.setPosition((WIDTH/2) - (rectangle.getSize().x/2), rectangle.getPosition().y);
}
