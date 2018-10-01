#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include<functional>
#include<string>

namespace gui {

class Button
{
public:
    Button(const std::string& message,
           const sf::Vector2f& size,
           std::function<void()> func);

    void draw(sf::RenderTarget& render);
    void update(sf::RenderWindow& window);

    void setPosition(float x, float y);
private:
    std::function<void()> m_function;

    sf::Vector2f m_size;
    sf::RectangleShape m_body;
    sf::Text m_text;
    sf::Sound m_sound;

    bool m_highlighted;
};

}

#endif // BUTTON_H_INCLUDED
