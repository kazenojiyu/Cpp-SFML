#include "home.h"

Home::Home(){
  topLeft_armor = 4;
  topRight_armor = 4;
  bottomLeft_armor = 4;
  bottomRight_armor = 4;

  width_element = 33;
  height_element = 20;

  position.x = 0;
  position.y = 0;
}

void Home::setTexture(const sf::Texture &texture){
  topLeft_sprite.setTexture(texture);
  topRight_sprite.setTexture(texture);
  bottomLeft_sprite.setTexture(texture);
  bottomRight_sprite.setTexture(texture);

  topLeft_sprite.setTextureRect(sf::IntRect(0, 0, width_element, height_element));
  topRight_sprite.setTextureRect(sf::IntRect(width_element, 0, width_element, height_element));
  bottomLeft_sprite.setTextureRect(sf::IntRect(0, height_element, width_element, height_element));
  bottomRight_sprite.setTextureRect(sf::IntRect(width_element, height_element, width_element, height_element));
}

void Home::draw(sf::RenderTarget &target){
  target.draw(topLeft_sprite);
  target.draw(topRight_sprite);
  target.draw(bottomLeft_sprite);
  target.draw(bottomRight_sprite);
}

void Home::setPosition(const int &x, const int &y){
  position.x = x;
  position.y = y;

  topLeft_sprite.setPosition(position.x, position.y);
  topRight_sprite.setPosition(position.x + width_element, position.y);
  bottomLeft_sprite.setPosition(position.x, position.y + height_element);
  bottomRight_sprite.setPosition(position.x + width_element, position.y + height_element);
}

sf::Vector2f Home::getSize(){
  return sf::Vector2f(width_element*2, height_element*2);
}

void Home::checkCollision(std::vector<Missile*> missileInProgress){
  for(unsigned int i = 0; i < missileInProgress.size(); i ++){
    if(topLeft_armor > 0 && topLeft_sprite.getGlobalBounds().intersects(missileInProgress[i]->getGlobalBounds())){
      missileInProgress[i]->setDirection(0,0);
      topLeft_armor --;
      update_sprite(&topLeft_sprite, topLeft_armor);
      missileInProgress[i]->clear();
      missileInProgress.erase(missileInProgress.begin() + i);
			i--;
    }
    else if(topRight_armor > 0 && topRight_sprite.getGlobalBounds().intersects(missileInProgress[i]->getGlobalBounds())){
      missileInProgress[i]->setDirection(0,0);
      topRight_armor --;
      update_sprite(&topRight_sprite, topRight_armor);
      missileInProgress[i]->clear();
      missileInProgress.erase(missileInProgress.begin() + i);
			i--;
    }
    else if(bottomLeft_armor > 0 && bottomLeft_sprite.getGlobalBounds().intersects(missileInProgress[i]->getGlobalBounds())){
      missileInProgress[i]->setDirection(0,0);
      bottomLeft_armor --;
      update_sprite(&bottomLeft_sprite, bottomLeft_armor);
      missileInProgress[i]->clear();
      missileInProgress.erase(missileInProgress.begin() + i);
			i--;
    }
    else if(bottomRight_armor > 0 && bottomRight_sprite.getGlobalBounds().intersects(missileInProgress[i]->getGlobalBounds())){
      missileInProgress[i]->setDirection(0,0);
      bottomRight_armor --;
      update_sprite(&bottomRight_sprite, bottomRight_armor);
      missileInProgress[i]->clear();
      missileInProgress.erase(missileInProgress.begin() + i);
			i--;
    }
  }
} // checkCollision

void Home::update_sprite(sf::Sprite* sprite, const unsigned int &armor){
  sf::IntRect previous = sprite->getTextureRect();

  if(armor == 0)
      sprite->setTextureRect(sf::IntRect(0, 0, 0, 0));
  else
      sprite->setTextureRect(sf::IntRect(previous.left + 67, previous.top, previous.width, previous.height));
} // update_sprite
