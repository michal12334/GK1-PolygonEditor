#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"

class Polygon {
public:
    Polygon(const std::vector<sf::Vector2i>& points);
    void draw(Canvas* canvas);

private:
    std::vector<sf::Vector2i> points;
};
