#pragma once

#include <SFML/Graphics.hpp>
#include "../buttons/rectangleButton.h"

class UpperPanel : public sf::Drawable {
public:
    UpperPanel(sf::Vector2f size, sf::Vector2f position = sf::Vector2f(0, 0));
    ~UpperPanel();
    void setPadding(float padding);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Vector2f size;
    sf::Vector2f position;
    sf::RectangleShape rectangle;
    sf::Color color;
    float padding;

    Button* normalModeButton;
    Button* polygonEditModeButton;
    Button* relationAddModeButton;
};
