#include "Renderer.hpp"

#include <cmath>
#include <iostream>

Renderer::Renderer()
    : _tcon() {}

void Renderer::render(sf::RenderWindow* window, Vector2f objPosition, Vector2f position,
                      size_t textureId, double angle, double textureAngle, Vector2i textureOffset, Vector2f scale)
{
    Vector2i temp = _tcon.getSpriteSize(textureId);
    Vector2f pos = position + Vector2f(static_cast<double>(temp.x), static_cast<double>(temp.y))*(1.0/2);
    pos = Vector2f(pos.x*cos(angle) - pos.y*sin(angle),
                   pos.x*sin(angle) + pos.y*cos(angle));

    auto t = _tcon.sprite(pos + objPosition, textureId, textureOffset, Vector2i(temp.x*scale.x, temp.y*scale.y));
    t.setRotation(static_cast<float>((angle + textureAngle) * 360.0/ (M_PI * 2)));
    window->draw(t);
}

void Renderer::loadTextures(const std::vector<std::string>& filenames)
{
    _tcon.loadTextures(filenames);
}
