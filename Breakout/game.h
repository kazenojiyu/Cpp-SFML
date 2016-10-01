#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "config.h"
#include "brick.h"
#include "paddle.h"
#include "ball.h"

#ifndef GAME_H
#define GAME_H

class Game{
private:
	sf::RenderWindow window;
	sf::Event event;

	sf::Texture bgTexture;
	sf::Texture heartsTexture;
	sf::Sprite bgSprite;
	sf::Sprite heartSprite1;
	sf::Sprite heartSprite2;
	sf::Sprite heartSprite3;
	std::vector<std::vector<Brick>> brickMatrix;

	sf::Font arial_font;
	sf::Text score_text;
	sf::Text textIntro;
	sf::Text textWin;
	sf::Text textLoose;

	sf::SoundBuffer blip_buffer;
	sf::Sound blip_sound;

	Paddle player;
	Ball ball;
	int gameState;
	bool hitTopSide;

	unsigned int nbHit;
	unsigned int playerLife;
	unsigned int playerPoints;
	unsigned int nbBricksLines;
public:
	Game();
	bool init();
	void run();
private:
	void setup();
	void update();
	void checkCollision();
	void reset();
	void drawBricks(sf::RenderTarget &target);
	void updateScore();
	bool screenClear();
};

#endif
