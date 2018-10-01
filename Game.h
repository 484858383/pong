#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include<SFML/Graphics.hpp>

#include<vector>
#include<memory>

#include"States/BaseState.h"

class Game
{
public:
    Game();

    void run();

    void checkForClose();
    sf::RenderWindow& getWindow();

    void pushState(std::unique_ptr<BaseState> state);
    void popState();
private:
    sf::RenderWindow m_window;
    std::vector<std::unique_ptr<BaseState>> m_states;
};

#endif // GAME_H_INCLUDED
