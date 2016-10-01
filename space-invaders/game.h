#include <SFML/Graphics.hpp>
#include <vector>
#include "config.h"
#include "paddle.h"
#include "home.h"
#include "missile.h"
#include "alien.h"

#ifndef GAME_H
#define GAME_H

class Game{
private:
	sf::RenderWindow window;
	sf::Event event;

	sf::Font arial_font;
	sf::Text score_text;
	sf::Text textIntro;
	sf::Text textWin;
	sf::Text textLoose;

	sf::Clock clock_player_fire, clock_alien_move;

	Paddle player;
	Home home1, home2, home3;

	sf::Texture homeTexture;
	sf::Texture spaceshipTexture;
	sf::Texture alienTexture;

	int gameState;

	unsigned int playerLife;
	unsigned int playerPoints;

	bool alienDirectionLeft;

	std::vector<Missile*> missileInProgress;
	std::vector<std::vector<Alien*>> alienInProgress;

public:
	Game();
	bool init();
	void run();
private:
	void setup();
	void processEvents();
	void update();
	void render();
	void checkCollision();
	void reset();
	void updateScore();
	void fire();
	void drawMissiles(sf::RenderTarget &target);
	void drawAliens(sf::RenderTarget &target);
	void missiles_update();
	void aliens_update();
};

#endif
