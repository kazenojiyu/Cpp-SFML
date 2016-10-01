#include "game.h"

Game::Game(){}

/**
 * Game initialization
 */
bool Game::init(){
	if (!arial_font.loadFromFile("resources/fonts/arial.ttf"))
		return false;

  if (!homeTexture.loadFromFile("resources/images/home.png"))
		return false;

  if (!spaceshipTexture.loadFromFile("resources/images/spaceship.png"))
		return false;

  if (!alienTexture.loadFromFile("resources/images/aliensprite.png"))
		return false;

	setup();

  return true;
} // init

/**
 * Game setup (init variable, and position)
 */
void Game::setup(){
	playerPoints = 0;
  playerLife = 3;
	gameState = INTRO;
	alienDirectionLeft = false;

	window.create(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	updateScore();
	score_text.setFont(arial_font);
	score_text.setCharacterSize(24);
	score_text.setPosition( (WIDTH/2) - (score_text.getGlobalBounds().width/2), 0);
	score_text.setColor(sf::Color(200,200,200,200));

	textIntro.setFont(arial_font);
	textIntro.setString("Press any key to play...");
	textIntro.setCharacterSize(24);
	textIntro.setColor(sf::Color::Yellow);
	textIntro.setStyle(sf::Text::Bold);
	sf::FloatRect textIntroRect = textIntro.getLocalBounds();
	textIntro.setOrigin(textIntroRect.left + textIntroRect.width/2.0f, textIntroRect.top  + textIntroRect.height/2.0f);
	textIntro.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f - textIntroRect.height));

	textWin.setFont(arial_font);
	textWin.setString("You Win !!!");
	textWin.setCharacterSize(24);
	textWin.setColor(sf::Color::Green);
	textWin.setStyle(sf::Text::Bold);
	sf::FloatRect textWinRect = textWin.getLocalBounds();
	textWin.setOrigin(textWinRect.left + textWinRect.width/2.0f, textWinRect.top  + textWinRect.height/2.0f);
	textWin.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));

	textLoose.setFont(arial_font);
	textLoose.setString("Game Over ...");
	textLoose.setCharacterSize(24);
	textLoose.setColor(sf::Color::Red);
	textLoose.setStyle(sf::Text::Bold);
	sf::FloatRect textLooseRect = textLoose.getLocalBounds();
	textLoose.setOrigin(textLooseRect.left + textLooseRect.width/2.0f, textLooseRect.top  + textLooseRect.height/2.0f);
	textLoose.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));

  sf::Vector2f home_size = home1.getSize();
  home1.setTexture(homeTexture);
  home2.setTexture(homeTexture);
  home3.setTexture(homeTexture);
  home1.setPosition((WIDTH/3) - (4*home_size.x/2), HEIGHT - 100);
  home2.setPosition((2*WIDTH/3) - (4*home_size.x/2), HEIGHT - 100);
  home3.setPosition(WIDTH - (4*home_size.x/2), HEIGHT - 100);
	// TODO : add a home

	for(unsigned int i = 0; i < NB_LINE_ALIEN; i ++){
		std::vector<Alien*> vec;
		for(unsigned int j = 0; j < NB_ALIENS_PER_LINES; j ++){
			Alien* a = new Alien(1);
			a->setPosition((j+1) * 40, (i+1) * 30);
			vec.push_back(a);
		}
		alienInProgress.push_back(vec);
	}

  player.setTexture(spaceshipTexture);

	reset();
} // setup

/**
 * Game main loop
 */
void Game::run(){
    while(window.isOpen()) {
				processEvents();
        update();
				render();
    }
} // run

void Game::processEvents(){
	while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
					window.close();
			else if( (gameState == INTRO || gameState == PAUSE) && event.type == sf::Event::KeyPressed)
					gameState = PLAYING;
			else if( gameState == PLAYING && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					gameState = PAUSE;
	}
} // processEvents

/**
 * Update game data and display
 */
void Game::update(){
	if(gameState == PLAYING){
		fire();
		checkCollision();
		missiles_update();
		aliens_update();
    player.update();
	}
} // update

void Game::render(){
	window.clear(sf::Color::Black);

	switch (gameState) {
		case INTRO:
		case PAUSE:
			window.draw(textIntro);
			break;
		case PLAYING:
			drawMissiles(window);
			drawAliens(window);
      player.draw(window);
      home1.draw(window);
      home2.draw(window);
      home3.draw(window);
			window.draw(score_text);
			break;
		case LOOSE:
			window.draw(textLoose);
			break;
		case WIN:
			window.draw(textWin);
			break;
	}

	window.display();
} // render

/**
 * Check collisions
 */
void Game::checkCollision(){
	// missile with top side
	for(unsigned int i = 0; i < missileInProgress.size(); i ++){
		if(missileInProgress[i]->getPosition().x <= 0){
			missileInProgress[i]->clear();
			delete missileInProgress[i];
			missileInProgress.erase(missileInProgress.begin() + i);
			i--;
		}
	}

	// missile with homes
	home1.checkCollision(missileInProgress);
	home2.checkCollision(missileInProgress);
	home3.checkCollision(missileInProgress);

	// alien with bottom side
	for(unsigned int i = NB_LINE_ALIEN; i > 0; i--){
		for(unsigned int j = 0; j < NB_ALIENS_PER_LINES; j++){
			sf::Vector2f alien_pos = alienInProgress[i-1][j]->getPosition();
			sf::Vector2f alien_size = alienInProgress[i-1][j]->getSize();
			if(alien_pos.y + alien_size.y >= HEIGHT){
				gameState = LOOSE;
				break;
			}
		}
		if(gameState == LOOSE)
			break;
	}

} // checkCollision

/**
 * Reset game parameter
 */
void Game::reset(){

} // reset

/**
 * Update score label
 */
void Game::updateScore(){
	score_text.setString( "Score : "+std::to_string(playerPoints) );
} // updateScore

void Game::fire(){
	// player fire
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		sf::Time elapsed = clock_player_fire.getElapsedTime();
		if(elapsed.asSeconds() >= 0.1f){
			sf::Vector2f player_pos = player.getPosition();
			sf::Vector2f player_size = player.getSize();
			Missile* new_m = new Missile( sf::Vector2f(player_pos.x + (player_size.x/2) - 2, player_pos.y - 10.0f) );
			new_m->setDirection(0, -2);
			missileInProgress.push_back(new_m);
			clock_player_fire.restart();
		}
	}
} // fire

void Game::drawMissiles(sf::RenderTarget &target){
	for(unsigned int i = 0; i < missileInProgress.size(); i ++){
		missileInProgress[i]->draw(target);
	}
} // drawMissiles

void Game::drawAliens(sf::RenderTarget &target){
	for(unsigned int i = 0; i < NB_LINE_ALIEN; i ++){
		for(unsigned int j = 0; j < NB_ALIENS_PER_LINES; j ++){
			alienInProgress[i][j]->draw(target);
		}
	}
} // drawAliens

void Game::missiles_update(){
	for(unsigned int i = 0; i < missileInProgress.size(); i ++){
		missileInProgress[i]->update();
	}
} // missiles_update

void Game::aliens_update(){
	sf::Time elapsed = clock_alien_move.getElapsedTime();
	if(elapsed.asSeconds() >= 0.5f){
		if(!alienDirectionLeft){
			sf::Vector2f alien_size = alienInProgress[0][0]->getSize();
			sf::Vector2f alien_pos = alienInProgress[0][0]->getPosition();
			if(alien_pos.x <= 0){
				for(unsigned int i = 0; i < NB_LINE_ALIEN; i ++){
					for(unsigned int j = 0; j < NB_ALIENS_PER_LINES; j ++){
						alienInProgress[i][j]->move(0, alien_size.y);
					}
				}
				alienDirectionLeft = true;
			}else{
				for(unsigned int i = 0; i < NB_LINE_ALIEN; i ++){
					for(unsigned int j = 0; j < NB_ALIENS_PER_LINES; j ++){
						alienInProgress[i][j]->move(-alien_size.x/2, 0);
					}
				}
			}
		}else if(alienDirectionLeft){
			sf::Vector2f alien_size = alienInProgress[0][NB_ALIENS_PER_LINES-1]->getSize();
			sf::Vector2f alien_pos = alienInProgress[0][NB_ALIENS_PER_LINES-1]->getPosition();
			if(alien_pos.x + alien_size.x >= WIDTH){
				for(unsigned int i = 0; i < NB_LINE_ALIEN; i ++){
					for(unsigned int j = 0; j < NB_ALIENS_PER_LINES; j ++){
						alienInProgress[i][j]->move(0, alien_size.y);
					}
				}
				alienDirectionLeft = false;
			}else{
				for(unsigned int i = 0; i < NB_LINE_ALIEN; i ++){
					for(unsigned int j = 0; j < NB_ALIENS_PER_LINES; j ++){
						alienInProgress[i][j]->move(alien_size.x/2, 0);
					}
				}
			}
		}
		clock_alien_move.restart();
	}
} // aliens_update
