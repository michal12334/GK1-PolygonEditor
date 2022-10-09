#pragma once

#include "usingMode.h"
#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"
#include "../drawers/pointDrawer.h"
#include "../drawers/lineDrawer.h"
#include <vector>

class EditUsingMode : public UsingMode {
public:
    EditUsingMode(sf::Window* window, Canvas* canvas);
    virtual void update() override;

private:
    bool isMouseOnFirstPoint(sf::Vector2i mousePosition);

    sf::Window* window;
    Canvas* canvas;

    bool isMouseLeftButtonPressed = false;
    PointDrawer pointDrawer{5};
    LineDrawer lineDrawer{2};
    bool isPolygonBeingDrawn = false;
    std::vector<sf::Vector2i> points;
};
