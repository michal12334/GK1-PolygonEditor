#pragma once

#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"

class LineDrawer {
public:
    LineDrawer(Canvas* canvas, int thickness);
    void draw(sf::Vector2i startPoint, sf::Vector2i finishPoint);

private:
    void bresenham1(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void bresenham2(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void bresenham3(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void bresenham4(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void bresenham5(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void bresenham6(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void bresenham7(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void bresenham8(sf::Vector2i startPoint, sf::Vector2i finishPoint, int dx, int dy);
    void drawSquare12(int x, int y);
    void drawSquare34(int x, int y);
    void drawSquare56(int x, int y);
    void drawSquare78(int x, int y);

    int thickness;
    Canvas* canvas;
};
