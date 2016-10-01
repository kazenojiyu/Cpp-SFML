#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "snake.h"

#ifndef GAME_H
#define GAME_H

class Game{
private:
	sf::RenderWindow window;
    sf::Event event;
    Snake snake;

    sf::Vector2f food;
    sf::RectangleShape foodShape;

    sf::Font arialFont;
    sf::Text initText;
    sf::Text pauseText;
    sf::Text winText;
    sf::Text looseText;
    sf::Text scoreText;

    sf::SoundBuffer blipBuffer;
    sf::Sound blipSound;

    unsigned int currentState;
    unsigned int score;
public:
	Game();
	bool init();
	void run();
private:
	void update();
	void checkCollision();
	void generateFood();
	void updateScore();
	void reset();
};

#endif