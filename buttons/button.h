#pragma once

#include <SFML/Graphics.hpp>
#include <string>

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
    void setText(std::string str, sf::Vector2f textPosition, unsigned int size);

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

    sf::Font font;
    sf::Text text;
};
