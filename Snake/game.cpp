#include "game.h"

Game::Game(){}

/**
 * Game initialization
 */
bool Game::init(){
    currentState = INIT;
    score = 0;

    srand(time(NULL));

	window.create(sf::VideoMode(WIDTH, HEIGHT), "Snake");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

	foodShape.setSize(sf::Vector2f(ELEMENT_SIZE - 1, ELEMENT_SIZE - 1));
    foodShape.setOutlineThickness(0.5f);
    foodShape.setOutlineColor(sf::Color::Black);
    generateFood();

    if (!arialFont.loadFromFile("arial.ttf"))
    	return false;

    initText.setFont(arialFont);
    initText.setString("Press any key to start...");
    initText.setCharacterSize(30);
    initText.setColor(sf::Color::Yellow);
    sf::FloatRect initTextRect = initText.getLocalBounds();
	initText.setOrigin(initTextRect.left + initTextRect.width/2.0f, initTextRect.top  + initTextRect.height/2.0f);
	initText.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));

    pauseText.setFont(arialFont);
    pauseText.setString("Press any key to continue...");
    pauseText.setCharacterSize(30);
    pauseText.setColor(sf::Color::Yellow);
    sf::FloatRect pauseTextRect = pauseText.getLocalBounds();
	pauseText.setOrigin(pauseTextRect.left + pauseTextRect.width/2.0f, pauseTextRect.top  + pauseTextRect.height/2.0f);
	pauseText.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));

    winText.setFont(arialFont);
    winText.setString("You WIN !!!");
    winText.setCharacterSize(30);
    winText.setColor(sf::Color::Green);
    sf::FloatRect winTextRect = winText.getLocalBounds();
	winText.setOrigin(winTextRect.left + winTextRect.width/2.0f, winTextRect.top  + winTextRect.height/2.0f);
	winText.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));

    looseText.setFont(arialFont);
    looseText.setString("You Loose !!!");
    looseText.setCharacterSize(30);
    looseText.setColor(sf::Color::Red);
    sf::FloatRect looseTextRect = looseText.getLocalBounds();
	looseText.setOrigin(looseTextRect.left + looseTextRect.width/2.0f, looseTextRect.top  + looseTextRect.height/2.0f);
	looseText.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));

    scoreText.setFont(arialFont);
    scoreText.setCharacterSize(20);
    scoreText.setColor(sf::Color(255, 255, 255, 150));
    scoreText.setPosition(sf::Vector2f(10, 10));    
    updateScore();

    if (!blipBuffer.loadFromFile("blip.wav"))
        return false;
    blipSound.setBuffer(blipBuffer);

    return true;
}

/**
 * Game main loop
 */
void Game::run(){    

    while(window.isOpen()) {

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
            if( (currentState == INIT || currentState == PAUSE) && event.type == sf::Event::KeyPressed )
            	currentState = PLAYING;
            if( (currentState == LOOSE || currentState == WIN) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ){
                reset();
                currentState = PLAYING;
            }
            if( currentState == PLAYING && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
            	currentState = PAUSE;
        }
        update();        
    }
}

/**
 * Update game data and display
 */
void Game::update(){
	window.clear(sf::Color::Black);

	switch(currentState){
		case INIT:
			window.draw(initText);
            break;
        case PAUSE:
            window.draw(pauseText);
            break;
        case PLAYING:
            checkCollision();
            snake.update();
            window.draw(scoreText);
            window.draw(foodShape);
            snake.draw(window);
		    break;
		case WIN:
			window.draw(winText);
		    break;
		case LOOSE:
			window.draw(looseText);
		    break;
	}

    window.display();
}

/**
 * Check collision with border, snake tail, or food
 */
void Game::checkCollision(){
    sf::Vector2f head_position = snake.getHeadPosition();
    
    // collision with border
    if(head_position.x < 0 || head_position.y < 0 || head_position.x > WIDTH || head_position.y > HEIGHT){
        currentState = LOOSE;
    }
    // eating its own tail
    if( snake.eatingItsOwnTail() ){
    	currentState = LOOSE;
    }
    // collision with food
    if( snake.intersects(foodShape) ){
        score ++;
        updateScore();
        blipSound.play();
        generateFood();
        snake.addElement(false);
    }
}

/**
 * Generate food coordinates : not in the snake shape and in the grid
 */
void Game::generateFood(){
	do{
		food.x = rand() % (WIDTH + 1);
		food.y = rand() % (HEIGHT + 1);
		foodShape.setPosition(food.x, food.y);    
	}while(snake.intersects(foodShape) || !((int)food.x % ELEMENT_SIZE) || !((int)food.y % ELEMENT_SIZE) );
}

/**
 * Update score string with the new score integer
 */
void Game::updateScore(){
    scoreText.setString("Score : "+std::to_string(score));
}

/**
 * Reset game display and data
 */
void Game::reset(){
    score = 0;
    updateScore();

    snake.reset();
    generateFood();
    currentState = INIT;
}