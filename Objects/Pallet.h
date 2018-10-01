#ifndef PALLET_H_INCLUDED
#define PALLET_H_INCLUDED

#include<SFML/Graphics.hpp>
#include<random>

class Pallet
{
public:
    Pallet(float x, float y);

    void handleInput(float dt, bool left);
    void handleAI(const sf::Vector2f& ballPos, float dt);

    void draw(sf::RenderTarget& render);
    void setPosition(float x, float y);

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize()     const;
    bool contains(const sf::Vector2f& point);
private:
    sf::RectangleShape m_body;
    sf::Vector2f m_size;

    float m_velocity;
    float m_acceleration;
    float m_maxSpeed;

    std::default_random_engine m_rng;

};

#endif // PALLET_H_INCLUDED
