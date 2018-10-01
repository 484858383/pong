#ifndef PLAYINGSTATE_H_INCLUDED
#define PLAYINGSTATE_H_INCLUDED

#include<vector>
#include<utility>

#include"BaseState.h"

#include"../Objects/Pallet.h"
#include"../Objects/Ball.h"

class Game;

enum class gamemode
{
    wall  = 0,
    local = 1,
    ai    = 2
};

class PlayingState : public BaseState
{
public:
    PlayingState(Game& game, gamemode mode);

    void input()                        override;
    void update(float dt)               override;
    void draw(sf::RenderTarget& render) override;
private:
    Pallet m_player;
    Pallet m_otherPlayer;
    Ball m_ball;
    gamemode m_gamemode;

    sf::RectangleShape m_wall;
    std::pair<sf::Text, sf::Text> m_scoreText; //first is left, second is right
    std::pair<int, int> m_scores;

    bool m_ready;
    bool m_win;
    int m_winningScore;

    sf::Text m_readyText;
    sf::Text m_winnerText;

    sf::Sound m_winSound;
};

#endif // PLAYINGSTATE_H_INCLUDED
