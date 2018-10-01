#include"Button.h"

#include"../Resources.h"

namespace gui {

Button::Button(const std::string& message,
               const sf::Vector2f& size,
               std::function<void()>func)
:m_function(func), m_size(size), m_highlighted(false)
{
    m_text.setFont(Resources::get().getFont());
    m_text.setFillColor(sf::Color::White);

    m_body.setTexture(&Resources::get().getTexture("button"));
    m_sound.setBuffer(Resources::get().getSound("click"));

    m_text.setCharacterSize(m_size.x / 4.0f);
    m_body.setSize(m_size);

    m_text.setString(message);

    setPosition(0, 0); //align the body to the text
}

void Button::draw(sf::RenderTarget& render)
{
    render.draw(m_body);
    render.draw(m_text);
}

void Button::update(sf::RenderWindow& window)
{
    static sf::Clock timer;
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if(m_highlighted)
        m_text.setFillColor(sf::Color::Red);
    else
        m_text.setFillColor(sf::Color::White);

    if(m_body.getGlobalBounds().contains(mousePos))
    {
        m_highlighted = true;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer.getElapsedTime().asSeconds() >= 0.1f)
        {
            timer.restart();
            m_sound.play();
            m_function();
        }
        return;
    }
    m_highlighted = false;
}

void Button::setPosition(float x, float y)
{
    m_body.setPosition(x, y);

    m_text.setPosition(x + (x / 50.0f), y - (y / 50.0f));
}

}
