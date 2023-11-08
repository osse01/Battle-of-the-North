#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <iostream>


int const MENU_STATE { 0 };
int const GAME_STATE { 0 };

class State
//  =============   State CLASS    ===============
{
public:
    // CONSTRUCTORS / DESTRUCTORS
    State() = default;
    virtual ~State() = default;

    // FUNCTIONS
    virtual void handleEvent (sf::Event) = 0;
    virtual void updateLogic () = 0;
    virtual void renderFrame () = 0;
    virtual int getNextState () = 0;


};

#endif