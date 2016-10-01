/**
 * This is a remake of the legendary Pong game with SFML library.
 * It is possible to enhance this project in adding ball power, change ball velocity, add brick power, etc...
 */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>

// check if this is collision between two rectangle
bool intersects (const sf::RectangleShape & rect1,const sf::RectangleShape & rect2)
{
    sf::FloatRect r1=rect1.getGlobalBounds();
    sf::FloatRect r2=rect2.getGlobalBounds();
    return r1.intersects (r2);
}

// Game class
class Game{  
private:   
    sf::RenderWindow window;
    sf::Event event;

    sf::RectangleShape middleLine;
    sf::RectangleShape ball;
    sf::RectangleShape player1;
    sf::RectangleShape player2;

    sf::Font font_arial;
    sf::Text textIntro;
    sf::Text textWin;
    sf::Text textLoose;
    sf::Text score;
    sf::Text fps;

    sf::Vector2f ballSpeed;

    sf::Time time;

    sf::SoundBuffer soundBuffer1;
    sf::Sound blip_sound;

    const int width = 640;
    const int height = 480;

    int player1_speed = 2;
    int player2_speed = 2;
    unsigned int player1_score = 0;
    unsigned int player2_score = 0;

    enum GameState{ INTRO, PLAYING, WIN, LOOSE, WAIT};
    int currentState;

public:
    Game(){        
    }
    ~Game(){
    }


    // init game
    bool init(){
        window.create(sf::VideoMode(width, height), "Pong");
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
        
        if (!font_arial.loadFromFile("arial.ttf"))
            return false;

        if(!soundBuffer1.loadFromFile("blip.wav"))
            return false;

        ballSpeed.x = 3;
        ballSpeed.y = 3;

        currentState = INTRO;

        setup();

        return true;
    }

    // main game loop
    bool exec(){
        sf::Clock renderClock;
        while(window.isOpen()){

            time=renderClock.getElapsedTime();
            float fFps=1000000/time.asMicroseconds();
            std::stringstream s;
            s<<fFps<<" fps";
            fps.setString(s.str());
            renderClock.restart();
            
            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed)
                    window.close();
                else if( (currentState == INTRO || currentState == WAIT) && event.type == sf::Event::KeyPressed)
                    currentState = PLAYING;
            }
            update();
            display();
        }
        return EXIT_SUCCESS;
    }

private:

    // display all object
    void display(){
        window.clear(sf::Color::Black);

        switch(currentState){
            case INTRO:
                window.draw(textIntro);
                break;
            case WAIT:
                window.draw(textIntro);                
            case PLAYING:
                window.draw(score);        
                window.draw(fps);        
                window.draw(middleLine);        
                window.draw(ball);        
                window.draw(player1);
                window.draw(player2);
                break;
            case WIN:
                window.draw(textWin);
                break;
            case LOOSE:
                window.draw(textLoose);
                break;
            default:
                break;
        }
        

        window.display();
    } 

    // setup element
    void setup(){

        textIntro.setFont(font_arial);
        textIntro.setString("Press any key to start...");
        textIntro.setCharacterSize(24);
        textIntro.setColor(sf::Color::Yellow);
        textIntro.setStyle(sf::Text::Bold);
        sf::FloatRect textIntroRect = textIntro.getLocalBounds();
        textIntro.setOrigin(textIntroRect.left + textIntroRect.width/2.0f, textIntroRect.top  + textIntroRect.height/2.0f);
        textIntro.setPosition(sf::Vector2f(width/2.0f, height/2.0f - textIntroRect.height));

        textWin.setFont(font_arial);
        textWin.setString("You Win !!!");
        textWin.setCharacterSize(24);
        textWin.setColor(sf::Color::Green);
        textWin.setStyle(sf::Text::Bold);
        sf::FloatRect textWinRect = textWin.getLocalBounds();
        textWin.setOrigin(textWinRect.left + textWinRect.width/2.0f, textWinRect.top  + textWinRect.height/2.0f);
        textWin.setPosition(sf::Vector2f(width/2.0f, height/2.0f));

        textLoose.setFont(font_arial);
        textLoose.setString("You Loose ...");
        textLoose.setCharacterSize(24);
        textLoose.setColor(sf::Color::Red);
        textLoose.setStyle(sf::Text::Bold);
        sf::FloatRect textLooseRect = textLoose.getLocalBounds();
        textLoose.setOrigin(textLooseRect.left + textLooseRect.width/2.0f, textLooseRect.top  + textLooseRect.height/2.0f);
        textLoose.setPosition(sf::Vector2f(width/2.0f, height/2.0f));

        middleLine.setFillColor(sf::Color::White);
        middleLine.setOutlineColor(sf::Color(175,175,175,30));        
        middleLine.setOutlineThickness(2);
        middleLine.setPosition(width/2, 0);
        middleLine.setSize(sf::Vector2f(0, height));

        resetGame();

        score.setString("0   0");
        score.setFont(font_arial);
        score.setCharacterSize(24);
        score.setPosition(width/2-score.getGlobalBounds().width/2, 0);
        score.setColor(sf::Color(200,200,200,100));
 
        fps.setString("0");
        fps.setFont(font_arial);
        fps.setCharacterSize(24);
        fps.setPosition(fps.getGlobalBounds().width/2, 0);
        fps.setColor(sf::Color(200,200,200,100));
        
        blip_sound.setBuffer(soundBuffer1);
    }

    // reset position for player1, player2 and the ball
    void resetGame(){
        ball.setPosition(width/2, height/2);
        ball.setSize(sf::Vector2f(15, 15));
        ball.setFillColor(sf::Color::White);

        player1.setSize(sf::Vector2f(3, 90));
        player1.setPosition(50-12, height/2-25);
        player1.setFillColor(sf::Color(0,122,245));

        player2.setSize(sf::Vector2f(3, 90));
        player2.setPosition(width-50, height/2-25);
        player2.setFillColor(sf::Color(0,122,245));
    }

    // update element in game
    void update(){
        if(currentState != PLAYING)
            return ;

        updatePlayer1();
        updatePlayer2();
        checkCollisions();
        updateBall();
    }

    // update player1 brick
    void updatePlayer1(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player1.getPosition().y > 0){
            player1.move(0, -player1_speed);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&  player1.getPosition().y + player1.getSize().y < height){
            player1.move(0, player1_speed);
        }
    }

    // update player2 brick
    void updatePlayer2(){
        if(ball.getPosition().y < player2.getPosition().y && player2.getPosition().y > 0){
            player2.move(0, -player2_speed);
        }else if(ball.getPosition().y > player2.getPosition().y && player2.getPosition().y + player2.getSize().y < height){
            player2.move(0, player2_speed);
        }
    }

    void checkCollisions(){
        sf::Vector2f ballPos = ball.getPosition();
        
        
        // ckeck top and bottom collision
        if(ballPos.y <= 0 || ballPos.y + ball.getSize().y >= height){            
            ballSpeed.y = -ballSpeed.y;
            blip_sound.play();
        }
        // check collision between ball and players brick
        else if(intersects(ball, player1) || intersects(ball, player2)){
            ballSpeed.x = -ballSpeed.x;
            blip_sound.play();
        }
        // player1 loose
        else if(ballPos.x <= 0){
            player2_score++;
            if(player2_score >= 5)
                currentState = LOOSE;
            else{
                score.setString(std::to_string(player1_score)+"   "+std::to_string(player2_score));
                currentState = WAIT;
                resetGame();
            }
        }
        // player1 WIN
        else if(ballPos.x >= width){
            player1_score++;
            if(player1_score >= 5)
                currentState = WIN;
            else{
                score.setString(std::to_string(player1_score)+"   "+std::to_string(player2_score));
                currentState = WAIT;
                resetGame();
            }
        }

    }

    // move ball
    void updateBall(){
        ball.move(ballSpeed);
    }
};


int main()
{    
    Game game;
    if(!game.init())
        return EXIT_FAILURE;    

    return game.exec();
}