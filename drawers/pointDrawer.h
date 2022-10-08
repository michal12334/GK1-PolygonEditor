#pragma once

#include "../canvases/canvas.h"
#include <SFML/Graphics.hpp>

class PointDrawer {
public:
    PointDrawer(int radius);
    void draw(Canvas* canvas, sf::Vector2i position);

private:
    int radius;
};
