#pragma once

#include "../canvases/canvas.h"
#include <SFML/Graphics.hpp>

class PointDrawer {
public:
    PointDrawer(Canvas* canvas, int radius);
    void draw(sf::Vector2i position, sf::Color color = sf::Color::Black);

private:
    int radius;
    Canvas* canvas;
};
