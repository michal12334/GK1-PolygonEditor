#pragma once

#include <SFML/Graphics.hpp>
#include "button.h"

class RectangleButton : public Button {
public:
    RectangleButton(sf::Vector2f size, sf::Vector2f position, sf::Color color = sf::Color::Black);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Color color;
    sf::RectangleShape rectangle;
};
