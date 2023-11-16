#include "GameState.h"

#include <iostream>
#include "utility"

GameState::GameState(sf::RenderWindow* screen,  sf::Music* sound, sf::Time* frameDuration)
:   melee {}, ranged {}, tank {}, State(sound, frameDuration), friendlyQueue {}, enemyQueue {},
    backgroundFile { "assets/background.jpeg" }, window { screen }, backgroundTexture {},
    backgroundSprite {}, zoomFactor { sf::Vector2f( 0.9f, 0.6f ) }, nextstate { GAME_STATE }, stage { 1 }
{
    window->setFramerateLimit(18);

    //  Load in Background Image
    if(!backgroundTexture.loadFromFile(backgroundFile))
    {
        throw std::logic_error(
        "    >> Error: Could Not Find background image. Error in GameState::GameState().");
    }
    backgroundSprite.setTexture(backgroundTexture);

    FileReader reader {};
    melee = reader.returnData("Melee", "assets/stage1.txt");
}

GameState::~GameState()
{
    frameDuration = nullptr;
}

void GameState::handleEvent(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Num1)
        {
            spawnFriendly();
        }
        if (event.key.code == sf::Keyboard::Num2)
        {
            spawnEnemy();
        }
        if (event.key.code == sf::Keyboard::M)
        {
            nextstate = MENU_STATE;
            music->stop();
        }
        if (event.key.code == sf::Keyboard::P)
        {
            nextstate = PAUSE_STATE;
            music->pause();
        }
        break;
    default:
        break;

    }
}

void GameState::updateLogic()         
{
    for(auto &it: friendlyQueue)
        {
            it->updatePos();
        }
    for(auto &it: enemyQueue)
        {
            it->updatePos();
        }

    handleCollisions();
}

void GameState::handleCollisions()
{
    // Handle Collision between Friendly and Enemy
    if ( friendlyQueue.size() > 0 && enemyQueue.size() > 0 )
    {
        if ( friendlyQueue.at(0)->collides(  enemyQueue.at(0) ) )
        {
            friendlyQueue.at(0) ->handleCollision(1);
            enemyQueue.at(0)    ->handleCollision(1);
        }
    }
    
    // Handle Collision between Enemies
    int behind{ 1 };
    for(int inFront{ 0 }; inFront < static_cast<int>(enemyQueue.size()) - 1; inFront++, behind++)
        { 
            if( enemyQueue.at(behind)->collides( enemyQueue.at(inFront) ) )
            {
                // Enemy Behind waits for Enemy in Front
                enemyQueue.at(behind)->handleCollision(0);
            }
        }
    
    // Handle Collision between Friends
    behind = 1;
    for( int inFront{ 0 }; inFront < static_cast<int>(friendlyQueue.size()) - 1; inFront++, behind++ )
        { 
            if( friendlyQueue.at(behind)->collides( friendlyQueue.at(inFront) ) )
            {
                // Friend Behind waits for Friend in Front
                friendlyQueue.at(behind)->handleCollision(0);
            }
        }

}

void GameState::renderFrame()  
{

    //  Fix Background
    window->clear(sf::Color(255, 255, 255));

    backgroundSprite.setScale(zoomFactor*0.694422f);
    
    window->draw(backgroundSprite);
    
    //  Render units
    for(auto &it: friendlyQueue)
        {
            window->draw(it->getSprite());
        }
    for(auto &it: enemyQueue)
        {
            window->draw(it->getSprite());
        }
}

void GameState::resetState()
{
    nextstate = GAME_STATE;
}

int GameState::getNextState()       
{
    return nextstate;
}

void GameState::spawnFriendly()
{
    friendlyQueue.push_back(std::make_shared<Melee> 
        ( melee, true, sf::Vector2f( 0.f, window->getSize().y-50.f ) ) );
    
}

void GameState::spawnEnemy()
{
    enemyQueue.push_back(std::make_shared<Melee> 
        ( melee, false, sf::Vector2f( window->getSize().x, window->getSize().y-50.f ) ) );
}

void GameState::updateStage()
{
    stage++;
}