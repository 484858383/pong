#include"Resources.h"

Resources& Resources::get()
{
    static Resources r;
    return r;
}

const sf::Texture& Resources::getTexture(const std::string& textureName)
{
    bool success = false;
    if(m_textures.find(textureName) != m_textures.end())
        success = true;
    else
        success = add(textureName, resource_type::texture);
    if(success)
        return m_textures[textureName];
    return m_textures["error"];
}

const sf::SoundBuffer& Resources::getSound(const std::string& fileName)
{
    bool success = false;
    if(m_sounds.find(fileName) != m_sounds.end())
        success = true;
    else
        success = add(fileName, resource_type::sound);
    if(success)
        return m_sounds[fileName];
    return m_sounds["error"];
}

const sf::Font& Resources::getFont() const
{
    return m_font;
}

Resources::Resources()
{
    add("error", resouce_type::texture);
    add("error", resouce_type::sound);
    m_font.loadFromFile("res/pixel.ttf");
}

bool Resources::add(const std::string& fileName, resource_type type)
{
    if(type == resource_type::sound)
    {
        sf::SoundBuffer b;
        if(b.loadFromFile("res/Sounds/" + fileName + ".wav"))
        {
            m_sounds[fileName] = b;
            return true;
        }
        return false;
    }
    else if(type == resource_type::texture)
    {
        sf::Texture t;
        if(t.loadFromFile("res/Textures/" + fileName + ".png"))
        {
            m_textures[fileName] = t;
            return true;
        }
        return false;
    }
    return false;
}
