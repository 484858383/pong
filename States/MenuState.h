#ifndef MENUSTATE_H_INCLUDED
#define MENUSTATE_H_INCLUDED

#include<SFML/Graphics.hpp>

#include<vector>

#include"BaseState.h"
#include"../GUI/Button.h"

class Game;

class MenuState : public BaseState
{
public:
    MenuState(Game& game);

    void input()                        override;
    void update(float dt)               override;
    void draw(sf::RenderTarget& render) override;
private:
    std::vector<gui::Button> m_buttons;
    sf::RectangleShape m_bg;
};

#endif // MENUSTATE_H_INCLUDED
