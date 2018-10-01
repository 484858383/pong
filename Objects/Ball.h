#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class Pallet;

class Ball
{
public:
    Ball();

    void draw(sf::RenderTarget& render);
    void update(float dt);
    void setPosition(float x, float y);

    void handleCollision(Pallet& other);
    void handleEdgeCollision(bool wallMode = false);

    void reset(bool left);

    const sf::Vector2f& getPosition() const;
private:
    sf::CircleShape m_body;
    sf::Vector2f m_velocity;
    sf::Sound m_bounceSound;

    float m_speed;
    float m_radius;
    float m_angle;

    const long double pi = 3.14159265359;
};

#endif // BALL_H_INCLUDED
