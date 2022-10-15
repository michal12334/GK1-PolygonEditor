#pragma once

#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"

class LineDrawer {
public:
    LineDrawer(Canvas* canvas);
    void draw(sf::Vector2i startPoint, sf::Vector2i finishPoint);

private:
    void bresenham1(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void bresenham2(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void drawPoint(int x, int y);

    Canvas* canvas;
};
