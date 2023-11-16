#include "../include/MenuState.h"

#include <iostream>
#include <cmath>

MenuState::MenuState(sf::RenderWindow* screen, sf::Music* sound, sf::Time* frameDuration)
:   State(sound, frameDuration), scale{1.0f}, t{0.0f}, nextState{MENU_STATE}, fontFile{"assets/coolFont.ttf"}, backgroundFile{"assets/background.jpeg"},
    texture{}, sprite{}, textFont{}, gameTitle{}, instructionText{},
    window{screen}, zoomFactor{sf::Vector2f(0.9f, 0.6f)}, gui { 0, screen }
//  -------------------------------------------------------
//  MenuState constructor. Loads in the Font Used for Text and background Image, the Name of the Files
//  are Saved in the fontFile and backgroundFile Variables.
//
//  For Now File Names are Hardcoded Values. This must Change!!!
//  -------------------------------------------------------
{
    if(texture.loadFromFile(backgroundFile))
    {
        sprite.setTexture(texture);
        //sprite.setScale(zoomFactor);
        sprite.setScale(window->getSize().x /sprite.getGlobalBounds().width, window->getSize().y /sprite.getGlobalBounds().height);
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find background image. Error in MenuState::MenuState().");
    }

    if(textFont.loadFromFile(fontFile))
    {
        gameTitle.setFont(textFont);
        gameTitle.setString("AGE OF WAR");
        gameTitle.setCharacterSize(75);
        gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2, gameTitle.getLocalBounds().height / 2);
        gameTitle.setPosition(window->getSize().x / 2, window->getSize().y / 3);
        gameTitle.setFillColor(sf::Color::Black); 

        instructionText.setFont(textFont);
        instructionText.setString("PRESS ANY KEY TO START");
        instructionText.setCharacterSize(20);
        instructionText.setOrigin(instructionText.getLocalBounds().width / 2, instructionText.getLocalBounds().height / 2);
        instructionText.setPosition(window->getSize().x / 2, window->getSize().y / 1.8);
        instructionText.setFillColor(sf::Color::Black); 
    }
    else
    {
        throw std::logic_error("    >> Error: Could Not Find font .ttf file. Error in MenuState::MenuState().");
    }
}

MenuState::~MenuState()
{
    window = nullptr;
    frameDuration = nullptr;
}

void MenuState::handleEvent(sf::Event event)
//  ---------------------------------------------
//  Handle Event, For Now We Can Only Start Game.
//  ---------------------------------------------
{
    switch (event.type)
    {
    //case sf::Event::KeyPressed:
    //    startAnimation();
    //    *currentState = GAME_STATE;  
    //    music->play();      
    //    break;
    case sf::Event::MouseButtonPressed:
    {
        sf::Event::MouseButtonEvent mouse { event.mouseButton };
        if (mouse.button == sf::Mouse::Button::Left)
        {
            switch (gui.buttonClicked(MENU_STATE, mouse.x, mouse.y))
            {
                case 1:
                    startAnimation();
                    nextState = GAME_STATE;  
                    music->play();      
                    break;
                case 2:
                    break;
                case 3:
                    window->close();
                    break;
                default:
                    break;
            }
        }
        break;
    }
    
    default:
        break;
    }
}

int MenuState::getNextState()
//  ---------------------------------------------
//  Returns Wich State is The Next State.
//  ---------------------------------------------
{
    return  nextState;
}


void MenuState::resetState()
{
    nextState = MENU_STATE;
}

void MenuState::updateLogic()
//  ---------------------------------------------
//  Function to Handle User Input. User Input Triggers
//  an Event.
//  ---------------------------------------------
{}

void MenuState::startAnimation()
//  ---------------------------------------------
//  This Fuction Rescales the background Such That it
//  Looks like an animation.
//  ---------------------------------------------
{
    double  step{1};
    double  delay{0.5};
    double  stepBackground{1};
    float   backgroundScale{1};
    sf::Event event{};
    
    while (step > 0 && stepBackground >0)
    {
        window->clear(sf::Color(255, 255, 255));

        step -= 0.01;
        stepBackground -= 0.002;

        scale = std::pow(step, 2);
        backgroundScale = std::pow(stepBackground, 2);

        gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2, gameTitle.getLocalBounds().height / 2);
        gameTitle.setScale(zoomFactor*scale);

        instructionText.setOrigin(instructionText.getLocalBounds().width / 2, instructionText.getLocalBounds().height / 2);
        instructionText.setScale(zoomFactor*scale);

        //if(sprite.getGlobalBounds().width >= window->getSize().x)
        //{
        //    sprite.setScale(zoomFactor*backgroundScale);    
        //}
        window->pollEvent(event);
        if(event.type == sf::Event::KeyPressed)
        {
            return;
        }
        while(window->pollEvent(event))
        {

        }
        window->draw(sprite);
        window->draw(gameTitle);
        window->draw(instructionText);
        window->display();


        //sf::sleep(sf::milliseconds(delay)); 
    }

    //window->clear(sf::Color(255, 255, 255));

    //window->draw(*sprite);
    window->display();
}


void MenuState::renderFrame()
//  ---------------------------------------------
//  Funcion Explaination
//  ---------------------------------------------
{
    
    window->clear(sf::Color(255, 255, 255));

    t = t + 0.0003;
    scale = 1.0 + 0.1 * std::cos(t * M_PI * 2);

    //sprite.setScale(zoomFactor);

    gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2, gameTitle.getLocalBounds().height / 2);
    gameTitle.setScale(zoomFactor*scale);

    instructionText.setScale(zoomFactor);

    window->draw(sprite);
    window->draw(gameTitle);
    window->draw(instructionText);

    gui.draw(MENU_STATE, window);
}
