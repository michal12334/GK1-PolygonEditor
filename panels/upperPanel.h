#pragma once

#include <SFML/Graphics.hpp>
#include "../buttons/button.h"
#include "../usingModes/usingModesManager.h"

class UpperPanel : public sf::Drawable {
public:
    UpperPanel(
        sf::Window* window,
        UsingModesManager* usingModesManager,
        sf::Vector2f size,
        sf::Vector2f position = sf::Vector2f(0, 0),
        float padding = 5
    );
    ~UpperPanel();
    void update();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Window* window;
    UsingModesManager* usingModesManager;

    sf::Vector2f size;
    sf::Vector2f position;
    sf::RectangleShape rectangle;
    sf::Color color;
    float padding;

    Button* normalModeButton;
    Button* polygonEditModeButton;
    Button* relationAddModeButton;

    bool isMouseLeftButtonPressed = false;
};
