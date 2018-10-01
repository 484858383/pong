#include"MenuState.h"

#include"../Game.h"
#include"../Resources.h"
#include"PlayingState.h"

#include<iostream>

MenuState::MenuState(Game& game)
:BaseState(game)
{
    m_bg.setSize(sf::Vector2f(1024, 512));
    m_bg.setTexture(&Resources::get().getTexture("title screen"));

    auto quitButton = gui::Button("Quit", sf::Vector2f(128, 32), [&]()
                                  {
                                      m_game->getWindow().close();
                                      return;
                                  });
    quitButton.setPosition(840, 336);
    m_buttons.push_back(quitButton);

    auto aiButton = gui::Button("Play AI", sf::Vector2f(128, 32), [&]()
                                    {
                                        m_game->pushState(std::make_unique<PlayingState>(*m_game, gamemode::ai));
                                        return;
                                    });
    aiButton.setPosition(696, 336);
    m_buttons.push_back(aiButton);

    auto wallButton = gui::Button("Wall Mode", sf::Vector2f(128, 32), [&]()
                                    {
                                        m_game->pushState(std::make_unique<PlayingState>(*m_game, gamemode::wall));
                                        return;
                                    });
    wallButton.setPosition(840, 288);
    m_buttons.push_back(wallButton);

    auto localButton = gui::Button("Play Local", sf::Vector2f(128, 32), [&]()
                                    {
                                        m_game->pushState(std::make_unique<PlayingState>(*m_game, gamemode::local));
                                        return;
                                    });
    localButton.setPosition(696, 288);
    m_buttons.push_back(localButton);
}

void MenuState::input()
{
    //...
}

void MenuState::update(float dt)
{
    for(auto& button : m_buttons)
        button.update(m_game->getWindow());
}

void MenuState::draw(sf::RenderTarget& render)
{
    render.draw(m_bg);
    for(auto& button : m_buttons)
        button.draw(render);
}
