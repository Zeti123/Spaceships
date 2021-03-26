#ifndef TEXTURECONTAINER_HPP
#define TEXTURECONTAINER_HPP

#include <SFML/Graphics.hpp>
#include "Vector2f.hpp"
#include "Vector2i.hpp"

class TextureContainer
{
public:
    void loadTexture(const std::string& filename);
    void loadTextures(const std::vector<std::string>& filenames);
    const sf::Sprite& sprite(Vector2f position, size_t id,Vector2i leftUp, Vector2i rightDown);
    Vector2i getSpriteSize(size_t id) const;

private:
    std::vector<sf::Texture*> _tex;
    std::vector<sf::Sprite> _textures;
};

#endif // TEXTURECONTAINER_HPP
