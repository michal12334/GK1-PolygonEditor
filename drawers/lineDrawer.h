#pragma once

#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"

class LineDrawer {
public:
    LineDrawer(Canvas* canvas);
    void draw(sf::Vector2i startPoint, sf::Vector2i finishPoint, sf::Color color = sf::Color::Black);

private:
    void bresenham1(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy, sf::Color color);
    void bresenham2(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy, sf::Color color);
    void drawPoint(int x, int y, sf::Color color);

    Canvas* canvas;
};
