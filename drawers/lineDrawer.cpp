#include "lineDrawer.h"
#include <cmath>

using namespace sf;
using namespace std;

LineDrawer::LineDrawer(Canvas* canvas) {
    this->canvas = canvas;
}

void LineDrawer::draw(Vector2i startPoint, Vector2i finishPoint, Color color) {
    int dx = finishPoint.x - startPoint.x;
    int dy = finishPoint.y - startPoint.y;
    if(dx >= 0 && dy >= 0 && dx >= dy)
        bresenhamX(startPoint, finishPoint, dx, dy, color);
    else if(dx >= 0 && dy >= 0 && dx < dy)
        bresenhamY(startPoint, finishPoint, dx, dy, color);
    else if(dx < 0 && dy >= 0 && -dx >= dy)
        bresenhamX(finishPoint, startPoint, -dx, -dy, color);
    else if(dx < 0 && dy >= 0 && -dx < dy)
        bresenhamY(startPoint, finishPoint, dx, dy, color);
    else if(dx >= 0 && dy < 0 && dx >= -dy)
        bresenhamX(startPoint, finishPoint, dx, dy, color);
    else if(dx >= 0 && dy < 0 && dx < -dy)
        bresenhamY(finishPoint, startPoint, -dx, -dy, color);
    else if(dx < 0 && dy < 0 && -dx >= -dy)
        bresenhamX(finishPoint, startPoint, -dx, -dy, color);
    else if(dx < 0 && dy < 0 && -dx < -dy)
        bresenhamY(finishPoint, startPoint, -dx, -dy, color);
}

void LineDrawer::bresenhamX(Vector2i startPoint, Vector2i finishPoint, int dx, int dy, Color color) {
    int d = 2 * abs(dy) - dx;
    int incrE = 2 * abs(dy);
    int incrNE = 2 * (abs(dy) - dx);
    int x = startPoint.x;
    int y = startPoint.y;
    drawPoint(x, y, color);
    while(x < finishPoint.x) {
        if(d < 0) {
            d += incrE;
            x += 1;
        } else {
            d += incrNE;
            x += 1;
            y += dy > 0 ? 1 : -1;
        }
        drawPoint(x, y, color);
    }
}

void LineDrawer::bresenhamY(Vector2i startPoint, Vector2i finishPoint, int dx, int dy, Color color) {
    int d = 2 * abs(dx) - dy;
    int incrE = 2 * abs(dx);
    int incrNE = 2 * (abs(dx) - dy);
    int x = startPoint.x;
    int y = startPoint.y;
    drawPoint(x, y, color);
    while(y < finishPoint.y) {
        if(d < 0) {
            d += incrE;
            y += 1;
        } else {
            d += incrNE;
            x += dx > 0 ? 1 : -1;
            y += 1;
        }
        drawPoint(x, y, color);
    }
}

void LineDrawer::drawPoint(int x, int y, Color color) {
   canvas->setPixel(x, y, color);
}
