#pragma once

#include <SFML/Graphics.hpp>

class Canvas : public sf::Drawable {
public:
    Canvas(sf::Vector2i size, sf::Vector2f position);
    void setPixel(int x, int y, sf::Color color);
    sf::Vector2f getPosition();
    void updateTexture();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Vector2i size;
    sf::Vector2f position;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};
