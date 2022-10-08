#include "pointDrawer.h"

using namespace sf;

PointDrawer::PointDrawer(int radius) {
    this->radius = radius;
}

void PointDrawer::draw(Canvas* canvas, Vector2i position) {
    for(int x = position.x - radius; x <= position.x + radius; x++) {
        for(int y = position.y - radius; y <= position.y + radius; y++) {
            canvas->setPixel(x, y, Color::Black);
        }
    }
}
