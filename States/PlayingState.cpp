#include"PlayingState.h"

#include"../Resources.h"
#include"../Game.h"

#include<climits>

PlayingState::PlayingState(Game& game, gamemode mode)
:BaseState(game), m_player(896, 224), m_otherPlayer(128, 224),
 m_gamemode(mode), m_ready(false), m_win(false), m_winningScore(2)
{
    m_wall.setSize(sf::Vector2f(8, 512));

    m_scoreText.first.setFont(Resources::get().getFont());
    m_scoreText.first.setCharacterSize(96);
    m_scoreText.first.setPosition(32, -32);
    m_scoreText.first.setString("0");

    m_scoreText.second.setFont(Resources::get().getFont());
    m_scoreText.second.setCharacterSize(96);
    m_scoreText.second.setPosition(960, -32);
    m_scoreText.second.setString("0");

    m_scores.first  = 0;
    m_scores.second = 0;

    m_ball.reset(false);

    if(m_gamemode == gamemode::wall)
        m_scoreText.first.setPosition(512, -32);

    m_readyText.setFont(Resources::get().getFont());
    m_readyText.setCharacterSize(48);
    m_readyText.setPosition(372, 256);
    m_readyText.setString("Press space when ready");

    m_winnerText.setFont(Resources::get().getFont());
    m_winnerText.setCharacterSize(48);
    m_winnerText.setPosition(372, 256);
    m_winnerText.setString("Press space when ready");//only time this is seen before a win is in wallmode at start

    m_winSound.setBuffer(Resources::get().getSound("win_song"));
    m_winSound.setVolume(20.0f);

    if(m_gamemode == gamemode::wall)
        m_winningScore = std::numeric_limits<int>::max();
}

void PlayingState::input()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_ready = true;
        m_win   = false;

        m_winSound.stop();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        m_game->popState();
        return;
    }
}

void PlayingState::update(float dt)
{
    auto ballPos = m_ball.getPosition();

    if(!m_ready)
    {
        if(m_gamemode == gamemode::local)
            m_otherPlayer.handleInput(dt, true);

        else if (m_gamemode == gamemode::ai)
            m_otherPlayer.handleAI(ballPos, dt);

        m_player.handleInput(dt, false);
        return;
    }

    if(m_gamemode == gamemode::local)
    {
        //handle movement/collision logic
        m_player.handleInput(dt, false);
        m_otherPlayer.handleInput(dt, true);

        m_ball.update(dt);
        m_ball.handleEdgeCollision();

        m_ball.handleCollision(m_player);
        m_ball.handleCollision(m_otherPlayer);
        //handle score logic
        if(ballPos.x < -10.0f)
        {
            m_scores.second++;
            m_ball.reset(true);
            m_ready = false;
        }
        else if(ballPos.x > 1034.0f)
        {
            m_scores.first++;
            m_ball.reset(false);
            m_ready = false;
        }
    }
    else if(m_gamemode == gamemode::wall)
    {
        m_player.handleInput(dt, false);

        m_ball.update(dt);
        m_ball.handleEdgeCollision(true);

        m_ball.handleCollision(m_player);

        if(ballPos.x < 9.0f)
        {
            m_scores.first++;
        }
        else if(ballPos.x > 1034.0f)
        {
            m_winnerText.setCharacterSize(32);
            m_winnerText.setPosition(372, 256);

            m_winnerText.setString(std::string("You scored ") +
                                   std::to_string(m_scores.first) +
                                   std::string(" press space to play again"));

            m_winSound.play();
            m_scores.first = 0;
            m_ready = false;
            m_ball.reset(false);
        }

    }
    else if(m_gamemode == gamemode::ai)
    {
        m_player.handleInput(dt, false);
        m_otherPlayer.handleAI(m_ball.getPosition(), dt);

        m_ball.update(dt);
        m_ball.handleEdgeCollision();

        m_ball.handleCollision(m_player);
        m_ball.handleCollision(m_otherPlayer);

        if(ballPos.x < -10.0f)
        {
            m_scores.second++;
            m_ball.reset(true);
            m_ready = false;
        }
        else if(ballPos.x > 1034.0f)
        {
            m_scores.first++;
            m_ball.reset(false);
            m_ready = false;
        }
    }

    if(m_scores.first >= m_winningScore)
    {
        m_winnerText.setString("Player 1 wins,\npress space to play again");
        m_win = true;

        m_scores.first = 0;
        m_scores.second = 0;

        m_winSound.play();
    }
    if(m_scores.second >= m_winningScore)
    {
        m_winnerText.setString("Player 2 wins,\npress space to play again");
        m_win = true;

        m_scores.first = 0;
        m_scores.second = 0;

        m_winSound.play();
    }

    m_scoreText.first.setString(std::to_string(m_scores.first));
    m_scoreText.second.setString(std::to_string(m_scores.second));
}

void PlayingState::draw(sf::RenderTarget& render)
{
    m_player.draw(render);

    if(m_gamemode != gamemode::wall)
    {
        m_otherPlayer.draw(render);
        render.draw(m_scoreText.first);
        render.draw(m_scoreText.second);

        if(m_win)
            render.draw(m_winnerText);
        else if(!m_ready)
            render.draw(m_readyText);
    }

    else
    {
        render.draw(m_wall);
        render.draw(m_scoreText.first);

        if(!m_ready)
            render.draw(m_winnerText);
    }

    m_ball.draw(render);
}
