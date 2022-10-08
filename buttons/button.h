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
    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);

protected:
    sf::Vector2f size;
    sf::Vector2f position;

private:
};
