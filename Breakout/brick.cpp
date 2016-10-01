#include "brick.h"

Brick::Brick(const unsigned int &armor_p, const unsigned int &points_p, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color, const unsigned int &col){
	armor = armor_p;
	points = points_p;
	color_i = col;
	rectangle.setPosition(position);
	rectangle.setSize(size);
	rectangle.setFillColor(color);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color::Black);
}

sf::RectangleShape Brick::getShape(){
	return rectangle;
}

void Brick::draw(sf::RenderTarget &target){
	target.draw(rectangle);
}

unsigned int Brick::getArmor(){
	return armor;
}
unsigned int Brick::getPoints(){
	return points;
}

sf::Vector2f Brick::getPosition(){
	return rectangle.getPosition();
}

sf::Vector2f Brick::getSize(){
	return rectangle.getSize();
}

unsigned int Brick::decrementArmor(){
	if(armor > 0){
		armor --;
		// change brick color
		color_i --;
		rectangle.setFillColor(color_per_line[color_i]);
		// add brick point to player score
		if(armor == 0)
			return points;
	}
	return 0;
}
