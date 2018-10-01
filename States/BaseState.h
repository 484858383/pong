#ifndef BASESTATE_H_INCLUDED
#define BASESTATE_H_INCLUDED

#include<SFML/Graphics.hpp>

class Game;

class BaseState
{
public:
    BaseState(Game& game)
    :m_game(&game) {}

    virtual ~BaseState() = default;

    virtual void input()                        = 0;
    virtual void update(float dt)               = 0;
    virtual void draw(sf::RenderTarget& render) = 0;
protected:
    Game* m_game;
};

#endif // BASESTATE_H_INCLUDED
