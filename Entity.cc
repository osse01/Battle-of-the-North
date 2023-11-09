#include <SFML/Graphics.hpp>
#include "Entity.h"


unsigned    const GAME_WIDTH  { 640 };
unsigned    const GAME_HEIGHT { 320 };


Entity::Entity(bool FRIENDLY)
    :xpos{0}, ypos{GAME_HEIGHT/2}, 
    MVMSPD{0.5}, IS_FRIENDLY{FRIENDLY}, 
    hasCollided{false},
    rekt{sf::Vector2f{10.f, 40.f}}
{
    rekt.setFillColor(sf::Color::Blue);
    rekt.setPosition(xpos, ypos);
}

sf::RectangleShape Entity::render()
{
    return rekt;
}

bool Entity::collides(Entity* const other)
{
    // Check whether this collides with other
    return rekt.getGlobalBounds().intersects((other->render()).getGlobalBounds());
}

void Entity::updatePos()
{
    if (rekt.getPosition().x >= GAME_WIDTH)
    {
        xpos = 0;
    }
    xpos += MVMSPD;
    rekt.setPosition(xpos, ypos);
}