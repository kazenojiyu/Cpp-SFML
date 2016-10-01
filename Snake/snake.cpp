#include "snake.h"

Snake::Snake(){
    cptTicks = 0;
    speed = 3;
    maxSpeed = 10;
    reset();        
}

/**
 * Draw the snake in the display
 */
void Snake::draw(sf::RenderTarget &target){
    if(direction_vector.x == 0 && direction_vector.y == 0){
        sf::Vector2f head_position = list.at(0).getPosition();
        for(unsigned int i = 0; i < list.size(); i++){
            list.at(i).setPosition(head_position.x + (i * ELEMENT_SIZE), head_position.y);
            list.at(i).draw(target);
        }
    }else{
       for(unsigned int i = 0; i < list.size(); i++){
            list.at(i).draw(target);
        } 
    }
}

/**
 * Add an element in the snake
 */
void Snake::addElement(const bool &head){
	Snake_element elmt(head);
	
    list.push_back(elmt);
}

/**
 * Update snake by catching keyboard event and moving
 */
void Snake::update(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != DOWN)
        moveUp();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != LEFT)
        moveRight();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != UP)
        moveDown();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != RIGHT)
        moveLeft();
    else
        move();
}

/**
 * Get snake size
 */
int Snake::getSize(){
    return list.size();
}

/**
 * Get the snake head position
 */
sf::Vector2f Snake::getHeadPosition(){
	return list.at(0).getPosition();
}

/**
 * Test if the snake intersects with one another shape
 */
bool Snake::intersects(const sf::RectangleShape &rect){
	sf::FloatRect head=list.at(0).getShape().getGlobalBounds();
	sf::FloatRect r2=rect.getGlobalBounds();

	if(head.intersects (r2))
		return true;

	return false;
}

/**
 * Test if snake is eating its own tail
 */
bool Snake::eatingItsOwnTail(){
	if(list.size() < 5)
		return false;
	sf::FloatRect head=list.at(0).getShape().getGlobalBounds();
	for(unsigned int i = 4; i < list.size(); i ++){
		sf::FloatRect r2=list.at(i).getShape().getGlobalBounds();
		if(head.intersects(r2)){
			return true;
		}
	}
	return false;
}

/**
 * Reset game data and display
 */
void Snake::reset(){
    cptTicks = 0;
    speed = 3;	

    direction_vector = sf::Vector2f(0,0);

    list.clear();
    addElement(true);
    addElement(false);
    addElement(false);
}

/**
 * Move snake up
 */
void Snake::moveUp(){
    direction_vector = sf::Vector2f(0, -ELEMENT_SIZE);
    direction = UP;
    move();
}
/**
 * Move snake right
 */
void Snake::moveRight(){
    direction_vector = sf::Vector2f(ELEMENT_SIZE, 0);
    direction = RIGHT;
    move();
}
/**
 * Move snake down
 */
void Snake::moveDown(){
    direction_vector = sf::Vector2f(0, ELEMENT_SIZE);
    direction = DOWN;
    move();
}
/**
 * Move snake left
 */
void Snake::moveLeft(){
    direction_vector = sf::Vector2f(-ELEMENT_SIZE, 0);
    direction = LEFT;
    move();
}
/**
 * Move each snake element of ELEMENT_SIZE at the correct speed
 */
void Snake::move(){
    if(cptTicks == maxSpeed-speed){
        sf::Vector2f head_position = list.at(0).getPosition();
        sf::Vector2f position, previous_position;
        list.at(0).move(direction_vector);
        for(unsigned int i = 1; i < list.size(); i++){
            if(i == 1){
                position = head_position;
            }else{
                position = previous_position;
            }
            previous_position = list.at(i).getPosition();
            list.at(i).setPosition(position);

        }
        cptTicks = 0;
    }else{
        cptTicks ++;
    }
}
