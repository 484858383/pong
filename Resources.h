#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED

//this is a very simplified resource holder class as there are only a couple resources needed

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include<unordered_map>

enum class resource_type
{
    texture = 0,
    sound   = 1
};

struct Resources
{
public:
    //singleton class
    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;
    Resources(Resources&&) = delete;
    Resources&& operator=(const Resources&&) = delete;

    static Resources& get();

    const sf::Texture& getTexture(const std::string& textureName);
    const sf::SoundBuffer& getSound(const std::string& fileName);

    const sf::Font& getFont() const;
private:
    Resources();
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::SoundBuffer> m_sounds;
    sf::Font m_font;//only one font needed
private:
    bool add(const std::string& fileName, resource_type type);
};

#endif // RESOURCES_H_INCLUDED
