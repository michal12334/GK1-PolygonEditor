#pragma once

#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"

class LineDrawer {
public:
    LineDrawer(int thickness);
    void draw(Canvas* canvas, sf::Vector2i startPoint, sf::Vector2i finishPoint);

private:
    void drawSquare(Canvas* canvas, int x, int y);

    int thickness;
};
