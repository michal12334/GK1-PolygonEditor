#pragma once

#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"

class LineDrawer {
public:
    LineDrawer(int thickness);
    void draw(Canvas* canvas, sf::Vector2i startPoint, sf::Vector2i finishPoint);

private:
    void bresenham1(Canvas* canvas, sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void bresenham2(Canvas* canvas, sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void drawSquare12(Canvas* canvas, int x, int y);

    int thickness;
};
