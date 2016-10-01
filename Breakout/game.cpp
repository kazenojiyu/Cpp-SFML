#include "game.h"

Game::Game(){}

/**
 * Game initialization
 */
bool Game::init(){
  if(!bgTexture.loadFromFile("resources/images/space.jpg"))
  	return false;

  if(!heartsTexture.loadFromFile("resources/images/heart.png"))
  	return false;

	if (!arial_font.loadFromFile("resources/fonts/arial.ttf"))
		return false;

	if (!blip_buffer.loadFromFile("resources/sounds/blip.wav"))
		return false;

	setup();

  return true;
} // init

/**
 * Game setup (init variable, and position)
 */
void Game::setup(){
	nbBricksLines = 8;
	playerPoints = 0;
  playerLife = 3;
  nbHit = 0;
	gameState = INTRO;
  hitTopSide = false;

	window.create(sf::VideoMode(WIDTH, HEIGHT), "Breakout");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	bgSprite.setTexture(bgTexture);
	bgSprite.setTextureRect(sf::IntRect(0, 0, WIDTH, HEIGHT));
	bgSprite.setPosition(0, 0);

  heartSprite1.setTexture(heartsTexture);
  heartSprite1.setTextureRect(sf::IntRect(15, 0, 15, 14));
  heartSprite1.setPosition(25, HEIGHT - 30);

  heartSprite2.setTexture(heartsTexture);
  heartSprite2.setTextureRect(sf::IntRect(15, 0, 15, 14));
  heartSprite2.setPosition(50, HEIGHT - 30);

  heartSprite3.setTexture(heartsTexture);
  heartSprite3.setTextureRect(sf::IntRect(15, 0, 15, 14));
  heartSprite3.setPosition(75, HEIGHT - 30);

	score_text.setFont(arial_font);
	score_text.setCharacterSize(24);
	score_text.setPosition( (WIDTH/2) - (score_text.getGlobalBounds().width/2), 0);
	score_text.setColor(sf::Color(200,200,200,200));
	updateScore();

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

	blip_sound.setBuffer(blip_buffer);
	reset();
} // setup

/**
 * Game main loop
 */
void Game::run(){
    while(window.isOpen()) {
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
						else if( (gameState == INTRO || gameState == PAUSE) && event.type == sf::Event::KeyPressed)
								gameState = PLAYING;
						else if( gameState == PLAYING && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
								gameState = PAUSE;
        }
        update();
    }
} // run

/**
 * Update game data and display
 */
void Game::update(){
	window.clear(sf::Color::Black);

	window.draw(bgSprite);

	switch (gameState) {
		case INTRO:
		case PAUSE:
			window.draw(textIntro);
			break;
		case PLAYING:
			checkCollision();
			player.update();
			ball.update();

      window.draw(heartSprite1);
      window.draw(heartSprite2);
      window.draw(heartSprite3);
			window.draw(score_text);
			drawBricks(window);
			player.draw(window);
			ball.draw(window);
			break;
		case LOOSE:
			window.draw(textLoose);
			break;
		case WIN:
			window.draw(textWin);
			break;
	}

	window.display();
} // update

/**
 * Check collisions
 */
void Game::checkCollision(){
	// player with sides collisions
	sf::Vector2f player_pos = player.getPosition();
	sf::Vector2f player_size = player.getSize();
	unsigned int player_speed = player.getSpeed();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player_pos.x > player_speed){
		player.setPosition(player_pos.x - player_speed, player_pos.y);
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player_pos.x <= player_speed){
		player.setPosition(0, player_pos.y);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player_pos.x + player_size.x  < WIDTH - player_speed){
		player.setPosition(player_pos.x + player_speed, player_pos.y);
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player_pos.x + player_size.x  >= WIDTH - player_speed){
		player.setPosition(WIDTH - player_size.x, player_pos.y);
	}

	// ball with player collisions
	sf::FloatRect collision_result;
	sf::Vector2f ball_direction = ball.getDirection();
	if(ball.getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds(), collision_result)){
		blip_sound.play();
		sf::Vector2f player_center( player.getPosition().x + (player.getSize().x/2), player.getPosition().y + (player.getSize().y/2) );
		if(collision_result.top < player_center.y && collision_result.width > collision_result.height) // top
			ball_direction.y *= -1;
		else if(collision_result.left > player_center.x && collision_result.height > collision_result.width) // right
			ball_direction.x *= -1;
		else if(collision_result.top > player_center.y && collision_result.width > collision_result.height) // bottom
			ball_direction.y *= -1;
		else if(collision_result.left < player_center.x && collision_result.height > collision_result.width) // left
			ball_direction.x *= -1;
		else{
			ball_direction.x *= -1;
			ball_direction.y *= -1;
		}
		ball.setDirection(ball_direction);
	}

	// ball collisions width sides
	ball_direction = ball.getDirection();
	sf::Vector2f ball_pos = ball.getPosition();
	unsigned int ball_radius = ball.getRadius();

	if(ball_pos.x <= 0 || ball_pos.x + (ball_radius*2) >= WIDTH){ // left and right side
		ball_direction.x = - ball_direction.x;
	}
  // top side
	if(ball_pos.y <= 0){
    if(!hitTopSide){
      hitTopSide = true;
      sf::Vector2f pos = player.getPosition();
      sf::Vector2f size = player.getSize();
      size.x /= 2;
      pos.x = pos.x - (size.x/2);
      player.setSize(size);
      player.setPosition(pos);
    }
		ball_direction.y = - ball_direction.y;
	}
  // bottom side
	if(ball_pos.y + (ball_radius*2) >= HEIGHT){
    playerLife --;
    ball.reset();
    player.reset();
    ball_direction = ball.getDirection();
    switch (playerLife) {
      case 2:
        heartSprite3.setTextureRect(sf::IntRect(0, 0, 15, 14));
        gameState = PAUSE;
        break;
      case 1:
        heartSprite2.setTextureRect(sf::IntRect(0, 0, 15, 14));
        gameState = PAUSE;
        break;
      default:
		    gameState = LOOSE;
    }
  }
	ball.setDirection(ball_direction);

	// ball and bricks collisions
	ball_direction = ball.getDirection();
	for(unsigned int i = 0; i < nbBricksLines; i++){
		for(unsigned int j = 0; j < NB_BRICK_PER_LINE; j++){
			if(brickMatrix[i][j].getArmor() > 0){
				if(ball.getShape().getGlobalBounds().intersects(brickMatrix[i][j].getShape().getGlobalBounds(), collision_result)){
          nbHit++;
					blip_sound.play();
					sf::Vector2f brick_center( brickMatrix[i][j].getPosition().x + (brickMatrix[i][j].getSize().x/2), brickMatrix[i][j].getPosition().y + (brickMatrix[i][j].getSize().y/2) );
					if(collision_result.top < brick_center.y && collision_result.width > collision_result.height) // top
						ball_direction.y *= -1;
					else if(collision_result.left > brick_center.x && collision_result.height > collision_result.width) // right
						ball_direction.x *= -1;
					else if(collision_result.top > brick_center.y && collision_result.width > collision_result.height) // bottom
						ball_direction.y *= -1;
					else if(collision_result.left < brick_center.x && collision_result.height > collision_result.width) // left
						ball_direction.x *= -1;
					else{
						ball_direction.x *= -1;
						ball_direction.y *= -1;
					}
					ball.setDirection(ball_direction);
					playerPoints += brickMatrix[i][j].decrementArmor();

          // ball speed increases on the 4th and the 12th hit
          if(nbHit == 4 || nbHit == 12){
            ball.accelerate();
          }
				}
			}
		}
	} // for nbBricksLines

	updateScore();
  // no more brick = win
  if(screenClear())
    gameState = WIN;
} // checkCollision

/**
 * Reset game parameter
 */
void Game::reset(){
	// clear all bricks
	brickMatrix.clear();

	// generate all bricks
	std::vector<int> point_per_line = {7,7,5,5,3,3,1,1};
	std::vector<int> color_i_per_line = {4,4,3,3,2,2,1,1};
	std::vector<int> armor_per_line = {4,4,3,3,2,2,1,1};
	std::vector<sf::Color> color_per_line = {sf::Color::Red,sf::Color::Red,sf::Color(255,125,0),sf::Color(255,125,0),sf::Color::Green,sf::Color::Green,sf::Color::Yellow,sf::Color::Yellow};

	float brick_width = (WIDTH / nbBricksLines)-2;
	int brick_height = 15;
	float margin_top_brick = 3 * brick_height;
	int brick_margin = 1;

	for(unsigned int i = 0; i < nbBricksLines; i++){
		std::vector<Brick> tmp;
		for(unsigned int j = 0; j < NB_BRICK_PER_LINE; j++){
			Brick brick(
				armor_per_line[i], // armor
				point_per_line[i], // points
				sf::Vector2f(j*(brick_width + 2 * brick_margin) + brick_margin, i*(brick_height) + margin_top_brick), // position
				sf::Vector2f(brick_width, brick_height), // size
				color_per_line[i], // color
				color_i_per_line[i] // color number
			);
			tmp.push_back(brick);
		}
		brickMatrix.push_back(tmp);
	}

	// generate paddle
	int player_width = WIDTH/2 - brick_width/2;
	int player_height = HEIGHT - (3*brick_height);
	player.setPosition( sf::Vector2f(player_width, player_height) );
	player.setSize( sf::Vector2f(brick_width, brick_height/2) );

	// generate ball
	ball.reset();
  player.reset();
} // reset

/**
 * draw all bricks on the screen
 */
void Game::drawBricks(sf::RenderTarget &target){
	for(unsigned int i = 0; i < nbBricksLines; i++){
		for(unsigned int j = 0; j < NB_BRICK_PER_LINE; j++){
			if(brickMatrix[i][j].getArmor() > 0)
				brickMatrix[i][j].draw(target);
		}
	}
} // drawBricks

/**
 * Update score label
 */
void Game::updateScore(){
	score_text.setString( "Score : "+std::to_string(playerPoints) );
} // updateScore

/**
 * Test if there is at least one break on the screen
 */
bool Game::screenClear(){
  for(unsigned int i = 0; i < nbBricksLines; i++){
		for(unsigned int j = 0; j < NB_BRICK_PER_LINE; j++){
			if(brickMatrix[i][j].getArmor() > 0)
				return false;
		}
	}
  return true;
} // screenClear
