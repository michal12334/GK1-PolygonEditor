#include "pointDrawer.h"

using namespace sf;

PointDrawer::PointDrawer(Canvas* canvas, int radius) {
    this->radius = radius;
    this->canvas = canvas;
}

void PointDrawer::draw(Vector2i position, Color color) {
    for(int x = position.x - (radius + 1) / 2; x <= position.x + radius / 2; x++) {
        for(int y = position.y - (radius + 1) / 2; y <= position.y + radius / 2; y++) {
            canvas->setPixel(x, y, color);
        }
    }
}
