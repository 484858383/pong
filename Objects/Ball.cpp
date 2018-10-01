#include"Ball.h"

#include"Pallet.h"
#include"../Resources.h"

namespace
{
    //this function was taken from p5.js library
    template<typename T>
    T mapValue(T value, T start1, T stop1, T start2, T stop2)
    {
        return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    }
}

Ball::Ball()
:m_speed(400.0f), m_radius(4.0f)
{
    m_angle = 0.0;

    m_body.setRadius(m_radius);
    m_velocity.x = m_speed * std::cos(m_angle);
    m_velocity.y = m_speed * std::sin(m_angle);

    m_bounceSound.setBuffer(Resources::get().getSound("bounce"));
    m_bounceSound.setVolume(0.0f); //i dont think it sounds that good but it is available if wanted
}

void Ball::draw(sf::RenderTarget& render)
{
    render.draw(m_body);
}

void Ball::update(float dt)
{
    m_body.move(m_velocity * dt);
}

void Ball::setPosition(float x, float y)
{
    m_body.setPosition(x, y);
}

void Ball::handleCollision(Pallet& other)
{
    sf::Vector2f thisPos = m_body.getPosition();

    //create a line from centre of circle that extends one diameter
    sf::Vector2f thisProjected = thisPos;
    thisProjected.x += m_radius * (m_velocity.x / m_speed);
    thisProjected.y += m_radius * (m_velocity.y / m_speed);

    if(other.contains(thisProjected) || other.contains(thisPos))
    {
        m_bounceSound.play();
        //find what percentage of the way the ball hits the pallet
        float sectionHit = (thisPos.y - other.getPosition().y) / other.getSize().y;
        float deg = 0.0f;

        //find angle depending on which pallet and where the ball hits
        if(m_body.getPosition().x > 512.0f)
        {
            deg = mapValue(sectionHit, 0.0f, 1.0f, 0.0f, 45.0f);
            if(m_velocity.y < 0.0f)
                deg *= -1.0f;
        }
        else
        {
            deg = mapValue(sectionHit, 0.0f, 1.0f, 0.0f, 45.0f);
            if(m_velocity.y > 0.0f)
                deg *= -1.0f;
            deg += 180.0f;
        }


        float rad = (pi / 180.0f) * deg;

        //change direction
        m_velocity.x = m_speed * std::cos(rad);
        m_velocity.y = m_speed * std::sin(rad);

        m_velocity.x *= -1.0f;
    }
}

void Ball::handleEdgeCollision(bool wallMode)
{
    if(m_body.getPosition().y < 0 || m_body.getPosition().y > 512)
    {
        m_velocity.y *= -1.0f;
        m_bounceSound.play();
    }

    if(m_body.getPosition().x < 9 && wallMode)
    {
        m_velocity.x *= -1.0f;
        m_speed += 20.0f;

        m_bounceSound.play();
    }

}

const sf::Vector2f& Ball::getPosition() const
{
    return m_body.getPosition();
}

void Ball::reset(bool left)
{
    setPosition(512, 256);

    m_velocity.x = m_speed * std::cos(m_angle);
    m_velocity.y = m_speed * std::sin(m_angle);

    if(left)
        m_velocity.x *= -1.0f;
}
