#include"Game.h"

#include<SFML/System/Clock.hpp>

#include"States/PlayingState.h"
#include"States/MenuState.h"

Game::Game()
{
    m_window.create(sf::VideoMode(1024, 512), "Pong", sf::Style::Close);
    m_window.setFramerateLimit(120);

    pushState(std::make_unique<MenuState>(*this));
}

void Game::run()
{
    float dt = 0;
    while(m_window.isOpen() && !m_states.empty())
    {
        sf::Clock c;

        m_window.clear();

        m_states.back()->input();
        m_states.back()->update(dt);
        m_states.back()->draw(m_window);

        m_window.display();

        checkForClose();

        dt = c.getElapsedTime().asSeconds();
    }
}

void Game::checkForClose()
{
    sf::Event e;
    while(m_window.pollEvent(e))
    {
        if(e.type == sf::Event::Closed)
            m_window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            m_window.close();
    }
}

sf::RenderWindow& Game::getWindow()
{
    return m_window;
}

void Game::pushState(std::unique_ptr<BaseState> state)
{
    m_states.push_back(std::move(state));
}

void Game::popState()
{
    m_states.pop_back();
}
