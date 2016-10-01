#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cctype>

class Game{  
private:   
    static const int width = 800;
    static const int height = 600;

    sf::RenderWindow window;
    sf::Event event;

    sf::Font font;
    sf::Text title;
    sf::Text instruction1;
    sf::Text instruction2;
    sf::Text entered;
    sf::Text result;

    std::string valueEntered;
    int secret = 23;
    int valueInt = 0;
    int nb_try = 0;

public:
    Game(){        
    }
    ~Game(){
        
    }

    bool init(){
        /* initialize random seed: */
        srand (time(NULL));       
  
        window.create(sf::VideoMode(800, 600), "More or less");
        window.setVerticalSyncEnabled(true);

        if (!font.loadFromFile("arial.ttf"))
            return false;

        setup();

        return true;
    }

    bool run(){
        while(window.isOpen()){
            
            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed)
                    window.close(); 
                if (event.type == sf::Event::TextEntered)
                    checkTextEntered(event.text.unicode);
            }
            display();
        }
        return EXIT_SUCCESS;
    }

private:
    void display(){
        window.clear(sf::Color::Black);

        window.draw(title);
        window.draw(instruction1);
        window.draw(instruction2);
        window.draw(entered);        
        window.draw(result);        

        window.display();        
    }

    void setup(){
        title.setFont(font);
        title.setString("More or less");
        title.setCharacterSize(24);
        title.setColor(sf::Color::Red);
        sf::FloatRect titleRect = title.getLocalBounds();
        title.setOrigin(titleRect.left + titleRect.width/2.0f, titleRect.top  + titleRect.height/2.0f);
        title.setPosition(sf::Vector2f(width/2.0f,titleRect.height));

        instruction1.setFont(font);
        instruction1.setString("A number was been chosen between 0 and 100.");
        instruction1.setCharacterSize(20);
        instruction1.setColor(sf::Color::Green);
        sf::FloatRect instructionRect1 = instruction1.getLocalBounds();
        instruction1.setOrigin(instructionRect1.left + instructionRect1.width/2.0f, instructionRect1.top  + instructionRect1.height/2.0f);
        instruction1.setPosition(sf::Vector2f(width/2.0f, 50 + instructionRect1.height));

        instruction2.setFont(font);
        instruction2.setString("Try to find this number :");
        instruction2.setCharacterSize(20);
        instruction2.setColor(sf::Color::Green);
        sf::FloatRect instructionRect2 = instruction2.getLocalBounds();
        instruction2.setOrigin(instructionRect2.left + instructionRect2.width/2.0f, instructionRect2.top  + instructionRect2.height/2.0f);
        instruction2.setPosition(sf::Vector2f(width/2.0f, 75 + instructionRect2.height));

        entered.setFont(font);
        entered.setString("");
        entered.setCharacterSize(18);
        entered.setColor(sf::Color::White);
        sf::FloatRect enteredRect = entered.getLocalBounds();
        entered.setOrigin(enteredRect.left + enteredRect.width/2.0f, enteredRect.top  + enteredRect.height/2.0f);
        entered.setPosition(sf::Vector2f(width/2.0f, 100 + enteredRect.height));

        result.setFont(font);
        result.setString("");
        result.setCharacterSize(30);
        result.setColor(sf::Color::Magenta);
        result.setStyle(sf::Text::Bold);
        sf::FloatRect resultRect = result.getLocalBounds();
        result.setOrigin(resultRect.left + resultRect.width/2.0f, resultRect.top  + resultRect.height/2.0f);
        result.setPosition(sf::Vector2f(width/2.0f, 200 + resultRect.height));

        secret = rand() % 100 + 1;
    }

    void checkTextEntered(const char c){
        result.setString("");
        if(c == '\r' || c == '\n'){
            if(valueEntered != ""){
                valueInt = std::stoi(valueEntered);
                valueEntered = "";
                showScore();
            }
        }else{
            valueEntered.append(sizeof(c), c);
            entered.setString(valueEntered);            
        }
    }

    void showScore(){
        nb_try ++;
        if(valueInt > secret){
            result.setString("WRONG : -");
            centerScore();
        }else if(valueInt < secret){
            result.setString("WRONG : +");
            centerScore();
        }else if(valueInt == secret){
            result.setString("You Won in "+std::to_string(nb_try)+" try.");
            centerScore();
        }else{
            std::cout << "error in showScore." << std::endl;
        }
    }

    void centerScore(){
        sf::FloatRect resultRect = result.getLocalBounds();
        result.setOrigin(resultRect.left + resultRect.width/2.0f, resultRect.top  + resultRect.height/2.0f);
        result.setPosition(sf::Vector2f(width/2.0f, 200 + resultRect.height));
    }


};


int main()
{    
    Game game;
    if(!game.init())
        return EXIT_FAILURE;    

    return game.run();
}