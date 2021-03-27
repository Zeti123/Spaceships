#include "Renderer.hpp"

#include <cmath>
#include <iostream>

Renderer::Renderer()
    : _tcon() {}

void Renderer::render(RenderSettings s)
{
    Vector2i temp = _tcon.getSpriteSize(s.textureId);
    Vector2f pos = s.position + Vector2f(static_cast<double>(temp.x), static_cast<double>(temp.y))*(1.0/2);
    pos = Vector2f(pos.x*cos(s.angle) - pos.y*sin(s.angle),
                   pos.x*sin(s.angle) + pos.y*cos(s.angle));

    auto t = _tcon.sprite(pos + s.objPosition, s.textureId, s.textureOffset, Vector2i(temp.x*s.scale.x, temp.y*s.scale.y));
    t.setRotation(static_cast<float>((s.angle + s.textureAngle) * 360.0/ (M_PI * 2)));
    if (t.getColor() != s.color)
        t.setColor(s.color);
    s.window->draw(t);
}

void Renderer::loadTextures(const std::vector<std::string>& filenames)
{
    _tcon.loadTextures(filenames);
}
