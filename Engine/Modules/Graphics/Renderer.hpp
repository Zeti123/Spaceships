#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "Vector2f.hpp"
#include "TextureContainer.hpp"

class Renderer
{
public:
    Renderer();
    void render(sf::RenderWindow* window, Vector2f objPosition, Vector2f position,
                size_t textureId, double angle, double textureAngle, Vector2i textureOffset, Vector2f scale);
    void loadTextures(const std::vector<std::string>& filenames);

private:
    TextureContainer _tcon;

};

#endif // RENDERER_HPP
