#include "../include/GUI.h"

#include <iostream>


GUI::GUI(int currentState, std::shared_ptr<sf::RenderWindow> window)
    : buttonSize { window->getSize().x/30 }, originalBaseHP{}, fontFile{ "assets/newFont.ttf" },
      interfaceFile{ "assets/interfaceBackground.jpeg" },
      coinFile{ "assets/gameCoin.png" }, heartFile{ "assets/health.png" },
      menuButtons {}, gameButtons {}, menuTexts{}, 
      gameTextures {}, 
      interface { sf::Vector2f(19*buttonSize/2.f, 2*buttonSize) },
      statsInterface { sf::Vector2f(7*buttonSize/2, 2*buttonSize) },
      healthBar{ sf::Vector2f(buttonSize/3, 6*buttonSize) }, enemyHealthBar{ healthBar },
      healthRec{ healthBar }, enemyHealthRec{ healthBar },
      interfaceTexture{}, coinTexture{}, heartTexture{}, coinSprite{}, heartSprite{}, font{}, goldText{},
      playText{}, optionsText{}, creditsText{}, quitText {}
{
    sf::Texture tmpText {};
    tmpText.loadFromFile("assets/cursor.png");
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile("assets/gameCoin.png");
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile("assets/health.png");
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile("assets/tree.png");
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile("assets/friendly_ranged_sprite_sheet.png");
        gameTextures.push_back(tmpText);
    tmpText.loadFromFile("assets/friendly_melee_sprite_sheet.png");
        gameTextures.push_back(tmpText);
    switch (currentState)
    {
    case MENU_STATE:
        {
            if ( font.loadFromFile(fontFile) )
            {
                menuTexts.push_back("Start game");

                menuTexts.push_back("Options");

                menuTexts.push_back("Credits");

                menuTexts.push_back("Quit");
            }
            else
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>)");
            }

           for (int i{0} ; i < menuTexts.size() ; i++)
            {
                menuButtons.push_back(std::make_shared<Button>(
                                            sf::Vector2f(3*buttonSize, buttonSize), 
                                            sf::Vector2f(window->getSize().x/2, window->getSize().y/2 + i * 1.2*buttonSize), 
                                            sf::Color(112, 58, 7), sf::Color::Black, menuTexts.at(i), font));
            }
            break;
        }

    case GAME_STATE:
        {
            if ( interfaceTexture.loadFromFile(interfaceFile) )
            {
                interface.setPosition(window->getSize().x - interface.getSize().x, 0.f);
                interface.setOutlineThickness(2.f);
                interface.setOutlineColor(sf::Color(0, 0, 0));
                interface.setTexture(&interfaceTexture);
                
                statsInterface.setPosition(0.f, 0.f);
                statsInterface.setOutlineThickness(2.f);
                statsInterface.setOutlineColor(sf::Color(0, 0, 0));
                statsInterface.setTexture(&interfaceTexture);
///////////////
                healthBar.setOrigin(0,healthBar.getGlobalBounds().height);
                healthBar.setPosition(buttonSize/2, 10*buttonSize);
                healthBar.setOutlineThickness(3.f);
                healthBar.setFillColor(sf::Color(109, 109, 110));
                healthBar.setOutlineColor(sf::Color(0, 0, 0));
                
                healthRec.setOrigin(0,healthRec.getGlobalBounds().height);
                healthRec.setPosition(healthBar.getPosition().x, healthBar.getPosition().y);
                healthRec.setOutlineThickness(3.f);
                healthRec.setFillColor(sf::Color(200, 10, 0));
                healthRec.setOutlineColor(sf::Color(0, 0, 0));
//////////////////
                enemyHealthBar.setOrigin(0,enemyHealthBar.getGlobalBounds().height);
                enemyHealthBar.setPosition(buttonSize/2, 10*buttonSize);
                enemyHealthBar.setOutlineThickness(3.f);
                enemyHealthBar.setFillColor(sf::Color(109, 109, 110));
                enemyHealthBar.setOutlineColor(sf::Color(0, 0, 0));

                enemyHealthRec.setOrigin(0,enemyHealthRec.getGlobalBounds().height);
                enemyHealthRec.setPosition(enemyHealthBar.getPosition().x, enemyHealthBar.getPosition().y);
                enemyHealthRec.setOutlineThickness(3.f);
                enemyHealthRec.setFillColor(sf::Color(200, 10, 0));
                enemyHealthRec.setOutlineColor(sf::Color(0, 0, 0));


            }
            else
            {
                throw std::logic_error("\n  >> Error. Could not load interfaceBackground file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>)");
            }

            if ( coinTexture.loadFromFile(coinFile) && heartTexture.loadFromFile(heartFile))
            {
                coinSprite.setTexture(coinTexture);
                coinSprite.setScale(0.0025*buttonSize, 0.0025*buttonSize);

                heartSprite.setTexture(heartTexture);
                heartSprite.setScale(0.00083*buttonSize, 0.000833*buttonSize);

            }
            else
            {
                throw std::logic_error("\n  >> Error. Could not load coin or heart icon file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>)");
            }

            if ( font.loadFromFile(fontFile) )
            {
                goldText.setFont(font);
                goldText.setCharacterSize(buttonSize*0.4);
                goldText.setColor(sf::Color::Yellow);
            }
            else
            {
                throw std::logic_error("\n  >> Error. Could not load font file. "
                "Error in GUI::GUI(int, std::shared_ptr<sf::RenderWindow>)");
            }

            for (int i{0} ; i < 6 ; i++)
            {
                sf::Sprite sprite {gameTextures.at(i)};
                if (i>3)
                {
                    sprite.setTextureRect(sf::IntRect(0,0,128,128));
                }
                gameButtons.push_back(std::make_shared<Button>(
                                            sf::Vector2f(buttonSize, buttonSize), 
                                            sf::Vector2f(window->getSize().x - 3*buttonSize/2 - i * 3*buttonSize/2, buttonSize/2), 
                                            sprite, sf::Color(128,128,128)));
            }
            break;
        }
    default:
        break;
    }
}

void GUI::draw(int currentState, std::shared_ptr<sf::RenderWindow> window, int gold)
//  ---------------------------------------------
{
    switch (currentState)
    {
        case MENU_STATE:
        {

            for (int i{0} ; i < menuButtons.size() ; i++)
            {
                window->draw(menuButtons.at(i)->draw());
            }
            break;
        }
        case GAME_STATE:
            window->draw(interface);
            window->draw(statsInterface);
            for (int i{0} ; i < 6 ; i++)
            {
                coinSprite.setPosition(0.5*buttonSize, 0.5*buttonSize);
                heartSprite.setPosition(0.5*buttonSize, 0.5*buttonSize + coinSprite.getGlobalBounds().height);


                goldText.setString(std::to_string(gold));
                goldText.setPosition(0.5*buttonSize + coinSprite.getGlobalBounds().width, 0.5*buttonSize);

                window->draw(goldText);
                window->draw(coinSprite);
                window->draw(heartSprite);
                window->draw(gameButtons.at(i)->draw());
            }
            break;
        default:
            break; 
    }
    
}

void GUI::updateLogic(std::shared_ptr<sf::RenderWindow> window, int currentState)
//  ---------------------------------------------
{
    sf::Mouse mouse{};
    for (int i{0} ; i < menuButtons.size() ; i++)
    {
        if (menuButtons.at(i)->getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
        {
            menuButtons.at(i)->hover();
        }
        else
        {
            menuButtons.at(i)->stopHover(); 
        }
    }
}

int GUI::buttonClicked(int currentState, float mouseX, float mouseY)
//  ---------------------------------------------
{
    switch (currentState)
    {
        case MENU_STATE:
        {
            for (int i{0} ; i < menuButtons.size() ; i++)
                {
                    if (menuButtons.at(i)->getGlobalBounds().contains(mouseX,mouseY))
                    {
                        return i+1;
                    }
                }
            break;
        }
        case GAME_STATE:
        {
            for (int i{0} ; i < 6 ; i++)
                {
                    if (gameButtons.at(i)->getGlobalBounds().contains(mouseX,mouseY))
                    {
                        return i+1;
                    }
                }
            break;
        }
        default:
            break;
    }
    return 0;
}

void GUI::setBaseHP(int hp) // Change later when Data is implemented correctly
{
    originalBaseHP = hp;
}

void GUI::drawHPBar(std::shared_ptr<sf::RenderWindow> window, int friendlyHP, int enemyHP)
{
    enemyHealthBar.setPosition(window->getSize().x - buttonSize/2*1.5, 8*buttonSize);
    enemyHealthBar.setScale(1/1.5, 1/1.5);
    enemyHealthRec.setPosition(enemyHealthBar.getPosition().x, enemyHealthBar.getPosition().y);
    enemyHealthRec.setScale(sf::Vector2f(1/1.5, static_cast<double>(enemyHP)/static_cast<double>(originalBaseHP)/1.5));
    
    healthBar.setPosition(buttonSize/2*1.5, 8*buttonSize);
    healthBar.setScale(1/1.5, 1/1.5);
    healthRec.setPosition(healthBar.getPosition().x, healthBar.getPosition().y);
    healthRec.setScale(sf::Vector2f(1/1.5, static_cast<double>(friendlyHP)/static_cast<double>(originalBaseHP)/1.5));

    window->draw(enemyHealthBar);
    window->draw(enemyHealthRec);
    window->draw(healthBar);
    window->draw(healthRec);

}