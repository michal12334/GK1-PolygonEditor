#include "pointDrawer.h"

using namespace sf;

PointDrawer::PointDrawer(Canvas* canvas, int radius) {
    this->radius = radius;
    this->canvas = canvas;
}

void PointDrawer::draw(Vector2i position) {
    for(int x = position.x - radius; x <= position.x + radius; x++) {
        for(int y = position.y - radius; y <= position.y + radius; y++) {
            canvas->setPixel(x, y, Color::Black);
        }
    }
}
