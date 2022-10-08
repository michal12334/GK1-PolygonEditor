#pragma once

#include "usingMode.h"
#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"
#include "../drawers/pointDrawer.h"

class EditUsingMode : public UsingMode {
public:
    EditUsingMode(sf::Window* window, Canvas* canvas);
    virtual void update() override;

private:
    sf::Window* window;
    Canvas* canvas;

    bool isMouseLeftButtonPressed = false;
    PointDrawer pointDrawer{5};
};
