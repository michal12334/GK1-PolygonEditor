#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
public:
    Button(sf::Vector2f size, sf::Vector2f position, int borderSize);
    bool isTouched(sf::Window* window);
    float getLeft();
    float getRight();
    float getUp();
    float getBottom();
    void setActive(bool active);
    bool isActive();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Vector2f size;
    sf::Vector2f position;
    sf::Color color;
    sf::RectangleShape rectangle;
    sf::RectangleShape borderLeft;
    sf::RectangleShape borderRight;
    sf::RectangleShape borderUp;
    sf::RectangleShape borderBottom;
    bool active;
};
