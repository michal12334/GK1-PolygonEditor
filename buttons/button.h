#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
public:
    Button(sf::Vector2f size, sf::Vector2f position);
    bool isClicked(sf::Window* window);
    float getLeft();
    float getRight();
    float getUp();
    float getBottom();

protected:
    sf::Vector2f size;
    sf::Vector2f position;

private:
};
