#include "lineDrawer.h"
#include <iostream>

using namespace sf;
using namespace std;

LineDrawer::LineDrawer(int thickness) {
    this->thickness = thickness;
}

void LineDrawer::draw(Canvas* canvas, Vector2i startPoint, Vector2i finishPoint) {
    int dx = finishPoint.x - startPoint.x;
    int dy = finishPoint.y - startPoint.y;
    if(dx >= 0 && dy >= 0 && dx >= dy)
        bresenham1(canvas, startPoint, finishPoint, dx, dy);
    else if(dx >= 0 && dy >= 0 && dx < dy)
        bresenham2(canvas, startPoint, finishPoint, dx, dy);
}

void LineDrawer::bresenham1(Canvas* canvas, Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = 2 * dy - dx;
    int incrE = 2 * dy;
    int incrNE = 2 * (dy - dx);
    int x = startPoint.x;
    int y = startPoint.y;
    cout << x << endl;
    drawSquare12(canvas, x, y);
    while(x < finishPoint.x) {
        cout << x << endl;
        if(d < 0) {
            d += incrE;
            x += thickness;
        } else {
            d += incrNE;
            x += thickness;
            y += thickness;
        }
        drawSquare12(canvas, x, y);
    }
}

void LineDrawer::bresenham2(Canvas* canvas, Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = 2 * dx - dy;
    int incrE = 2 * dx;
    int incrNE = 2 * (dx - dy);
    int x = startPoint.x;
    int y = startPoint.y;
    cout << x << endl;
    drawSquare12(canvas, x, y);
    while(y < finishPoint.y) {
        cout << x << endl;
        if(d < 0) {
            d += incrE;
            y += thickness;
        } else {
            d += incrNE;
            x += thickness;
            y += thickness;
        }
        drawSquare12(canvas, x, y);
    }
}

void LineDrawer::drawSquare12(Canvas* canvas, int x, int y) {
    #pragma omp parallel for
    for(int xx = x; xx < x + thickness; xx++) {
        #pragma omp parallel for
        for(int yy = y; yy < y + thickness; yy++) {
            canvas->setPixel(xx, yy, Color::Black);
        }
    }
}
