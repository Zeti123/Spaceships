#include "TextureContainer.hpp"

#include <iostream>

void TextureContainer::loadTexture(const std::string& filename)
{
    _tex.push_back(new sf::Texture);
    _textures.push_back({});
    _tex.back()->loadFromFile(filename);
    _textures.back().setTexture(*_tex.back());
    _textures.back().setOrigin(_tex.back()->getSize().x/2, _tex.back()->getSize().y/2);
}
void TextureContainer::loadTextures(const std::vector<std::string>& filenames)
{
    for (const auto& filename: filenames)
        loadTexture(filename);
}

const sf::Sprite& TextureContainer::sprite(Vector2f position, size_t id, Vector2i rectPos, Vector2i rectSize)
{
    size_t texturesSize = _tex.size();
    if (id >= texturesSize)
        throw "there is no such texture";

    _textures[id].setPosition(static_cast<float>(position.x),
                              static_cast<float>(position.y));
    _textures[id].setTextureRect(sf::IntRect(rectPos.x, rectPos.y, rectSize.x, rectSize.y));
    return _textures[id];
}

Vector2i TextureContainer::getSpriteSize(size_t id) const
{
    size_t texturesSize = _tex.size();
    if (id >= texturesSize)
        throw "there is no such texture";

    return Vector2i(static_cast<int>(_tex[id]->getSize().x), static_cast<int>(_tex[id]->getSize().y));
}
