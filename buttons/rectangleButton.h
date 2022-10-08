#pragma once

#include <SFML/Graphics.hpp>
#include "button.h"

class RectangleButton : public Button {
public:
    RectangleButton(sf::Vector2f size, sf::Vector2f position, sf::Color color = sf::Color::Black);
    virtual void setSize(sf::Vector2f size) override;
    virtual void setPosition(sf::Vector2f size) override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Color color;
    sf::RectangleShape rectangle;
};
