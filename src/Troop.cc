#include "../include/Troop.h"

#include <iostream>

Troop::Troop(const FileReader::Data& stats, bool friendly, sf::Vector2f pos, std::shared_ptr<sf::Time> frameDuration)
: Dynamic::Dynamic(stats, friendly, pos, frameDuration), damageCounter { 1 }, spriteCounter { 0 }
{}

void Troop::handleCollision(int troopState, int otherDamage)
{   
    if (Entity::isFriendly)    
    {
        Entity::xpos -= Dynamic::MOVEMENTSPEED * (frameDuration->asSeconds());
    }
    else
    {
        Entity::xpos += Dynamic::MOVEMENTSPEED * (frameDuration->asSeconds());
    }
    
    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);

    switch ( troopState ) {
        case 0:
            idle();
            break;
        case 1:
            attack(otherDamage);
            break;
        default:
            throw std::logic_error("    >>Error: The troopState does not exist!");
    }
}

void Troop::updatePos()
{
    if (!Entity::isFriendly)    
    {
        Entity::xpos -= Dynamic::MOVEMENTSPEED * (frameDuration->asSeconds());
    }
    else
    {
        std::cout << frameDuration->asSeconds() << std::endl;
        Entity::xpos += Dynamic::MOVEMENTSPEED * (frameDuration->asSeconds());
    }

    Entity::sprite.setPosition(Entity::xpos, Entity::ypos);
    Entity::boundingbox.setPosition(Entity::xpos, Entity::ypos);
    walk();
}

void Troop::changeSprite()
{
    if (spriteCounter * frameDuration->asSeconds() >= 0.04)
    {
        if(Entity::rectSourceSprite.left == 128*23)
            {
                Entity::rectSourceSprite.left = 0;
            }
            else
            {
                Entity::rectSourceSprite.left += 128;
            }
            Entity::sprite.setTextureRect(Entity::rectSourceSprite);
        spriteCounter = 0;
    }
    spriteCounter ++;
}

void Troop::walk()
{
    Entity::rectSourceSprite.top = 0;
    changeSprite();
}

void Troop::idle()
{
    Entity::rectSourceSprite.top = 128;
    changeSprite();
}

void Troop::attack(int otherDamage)
{
    Entity::rectSourceSprite.top = 256;
    changeSprite();
    if ( damageCounter == 25 )
    {
        Entity::hp -= otherDamage;
        damageCounter = 0;
    }
    damageCounter ++;

}