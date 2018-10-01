#include"Pallet.h"

Pallet::Pallet(float x, float y)
:m_size(8, 64), m_velocity(0), m_acceleration(25), m_maxSpeed(250), m_rng(std::time(nullptr))
{
    m_body.setSize(m_size);
    setPosition(x, y);
}

void Pallet::handleInput(float dt, bool left)
{
    sf::Keyboard::Key up , down;

    if(left)
    {
        up = sf::Keyboard::W;
        down = sf::Keyboard::S;
    }
    else
    {
        up = sf::Keyboard::Up;
        down = sf::Keyboard::Down;
    }

    if(sf::Keyboard::isKeyPressed(up))
    {
        m_velocity += m_acceleration;
    }
    if(sf::Keyboard::isKeyPressed(down))
    {
        m_velocity -= m_acceleration;
    }
    //limits
    if(m_velocity >= m_maxSpeed)
        m_velocity = m_maxSpeed;

    if(m_velocity <= -m_maxSpeed)
        m_velocity = -m_maxSpeed;

    //friction
    if(m_velocity < 0.0f)
        m_velocity += 2.5f;

    if(m_velocity > 0.0f)
        m_velocity -= 2.5f;

    float yPos = m_body.getPosition().y;
    float deltaTotal = 0.0f;

    if(yPos <= 0.0f)
    {
        float delta = 0.0f - yPos;
        deltaTotal += delta;
    }
    if(yPos >= 448.0f)
    {
        float delta = yPos - 448.0f;
        deltaTotal -= delta;
    }
    m_body.move(0, (-m_velocity * dt) + deltaTotal);
}

void Pallet::handleAI(const sf::Vector2f& ballPos, float dt)
{
    static std::uniform_int_distribution<> dist(256, 768);
    float reactionPos = dist(m_rng);

    if(ballPos.x < reactionPos)
    {
        if(ballPos.y > getPosition().y + 32) //64 = y height of object / 2.0
            m_velocity -= m_acceleration;
        else if(ballPos.y < getPosition().y + 32)
            m_velocity += m_acceleration;

    }
    if(m_velocity >= m_maxSpeed)
        m_velocity = m_maxSpeed;

    if(m_velocity <= -m_maxSpeed)
        m_velocity = -m_maxSpeed;

    //friction
    if(m_velocity < 0.0f)
        m_velocity += 2.5f;

    if(m_velocity > 0.0f)
        m_velocity -= 2.5f;

    float yPos = m_body.getPosition().y;
    float deltaTotal = 0.0f;

    if(yPos <= 0.0f)
    {
        float delta = 0.0f - yPos;
        deltaTotal += delta;
    }
    if(yPos >= 448.0f)
    {
        float delta = yPos - 448.0f;
        deltaTotal -= delta;
    }

    m_body.move(0, (-m_velocity * dt) + deltaTotal);
}

void Pallet::draw(sf::RenderTarget& render)
{
    render.draw(m_body);
}

void Pallet::setPosition(float x, float y)
{
    m_body.setPosition(x, y);
}

const sf::Vector2f& Pallet::getPosition() const
{
    return m_body.getPosition();
}

const sf::Vector2f& Pallet::getSize() const
{
    return m_body.getSize();
}

bool Pallet::contains(const sf::Vector2f& point)
{
    return m_body.getGlobalBounds().contains(point);
}
