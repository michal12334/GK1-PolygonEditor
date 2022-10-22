#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Canvas : public sf::Drawable {
public:
    Canvas(sf::Vector2i size, sf::Vector2f position);
    void setPixel(int x, int y, sf::Color color);
    sf::Vector2f getPosition();
    sf::Vector2i getSize();
    void updateTexture();
    void clear();
    void drawNative(sf::Drawable* drawable);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Vector2i size;
    sf::Vector2f position;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    std::vector<sf::Drawable*> drawables;
};
