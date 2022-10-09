#include "lineDrawer.h"

using namespace sf;

LineDrawer::LineDrawer(Canvas* canvas, int thickness) {
    this->thickness = thickness;
    this->canvas = canvas;
}

void LineDrawer::draw(Vector2i startPoint, Vector2i finishPoint) {
    int dx = finishPoint.x - startPoint.x;
    int dy = finishPoint.y - startPoint.y;
    if(dx >= 0 && dy >= 0 && dx >= dy)
        bresenham1(startPoint, finishPoint, dx, dy);
    else if(dx >= 0 && dy >= 0 && dx < dy)
        bresenham2(startPoint, finishPoint, dx, dy);
    else if(dx < 0 && dy >= 0 && -dx >= dy)
        bresenham3(startPoint, finishPoint, dx, dy);
    else if(dx < 0 && dy >= 0 && -dx < dy)
        bresenham4(startPoint, finishPoint, dx, dy);
    else if(dx >= 0 && dy < 0 && dx >= -dy)
        bresenham5(startPoint, finishPoint, dx, dy);
    else if(dx >= 0 && dy < 0 && dx < -dy)
        bresenham6(startPoint, finishPoint, dx, dy);
    else if(dx < 0 && dy < 0 && -dx >= -dy)
        bresenham7(startPoint, finishPoint, dx, dy);
    else if(dx < 0 && dy < 0 && -dx < -dy)
        bresenham8(startPoint, finishPoint, dx, dy);
}

void LineDrawer::bresenham1(Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = 2 * dy - dx;
    int incrE = 2 * dy;
    int incrNE = 2 * (dy - dx);
    int x = startPoint.x;
    int y = startPoint.y;
    drawSquare12(x, y);
    while(x < finishPoint.x) {
        if(d < 0) {
            d += incrE;
            x += thickness;
        } else {
            d += incrNE;
            x += thickness;
            y += thickness;
        }
        drawSquare12(x, y);
    }
}

void LineDrawer::bresenham2(Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = 2 * dx - dy;
    int incrE = 2 * dx;
    int incrNE = 2 * (dx - dy);
    int x = startPoint.x;
    int y = startPoint.y;
    drawSquare12(x, y);
    while(y < finishPoint.y) {
        if(d < 0) {
            d += incrE;
            y += thickness;
        } else {
            d += incrNE;
            x += thickness;
            y += thickness;
        }
        drawSquare12(x, y);
    }
}

void LineDrawer::bresenham3(Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = 2 * dy + dx;
    int incrE = 2 * dy;
    int incrNE = 2 * (dy + dx);
    int x = startPoint.x;
    int y = startPoint.y;
    drawSquare34(x, y);
    while(x > finishPoint.x) {
        if(d < 0) {
            d += incrE;
            x -= thickness;
        } else {
            d += incrNE;
            x -= thickness;
            y += thickness;
        }
        drawSquare34(x, y);
    }
}

void LineDrawer::bresenham4(Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = -2 * dx - dy;
    int incrE = -2 * dx;
    int incrNE = 2 * (-dx - dy);
    int x = startPoint.x;
    int y = startPoint.y;
    drawSquare34(x, y);
    while(y < finishPoint.y) {
        if(d < 0) {
            d += incrE;
            y += thickness;
        } else {
            d += incrNE;
            x -= thickness;
            y += thickness;
        }
        drawSquare34(x, y);
    }
}

void LineDrawer::bresenham5(Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = -2 * dy - dx;
    int incrE = -2 * dy;
    int incrNE = 2 * (-dy - dx);
    int x = startPoint.x;
    int y = startPoint.y;
    drawSquare56(x, y);
    while(x < finishPoint.x) {
        if(d < 0) {
            d += incrE;
            x += thickness;
        } else {
            d += incrNE;
            x += thickness;
            y -= thickness;
        }
        drawSquare56(x, y);
    }
}

void LineDrawer::bresenham6(Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = 2 * dx + dy;
    int incrE = 2 * dx;
    int incrNE = 2 * (dx + dy);
    int x = startPoint.x;
    int y = startPoint.y;
    drawSquare56(x, y);
    while(y > finishPoint.y) {
        if(d < 0) {
            d += incrE;
            y -= thickness;
        } else {
            d += incrNE;
            x += thickness;
            y -= thickness;
        }
        drawSquare56(x, y);
    }
}

void LineDrawer::bresenham7(Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = -2 * dy + dx;
    int incrE = -2 * dy;
    int incrNE = 2 * (-dy + dx);
    int x = startPoint.x;
    int y = startPoint.y;
    drawSquare78(x, y);
    while(x > finishPoint.x) {
        if(d < 0) {
            d += incrE;
            x -= thickness;
        } else {
            d += incrNE;
            x -= thickness;
            y -= thickness;
        }
        drawSquare78(x, y);
    }
}

void LineDrawer::bresenham8(Vector2i startPoint, Vector2i finishPoint, int dx, int dy) {
    int d = -2 * dx + dy;
    int incrE = -2 * dx;
    int incrNE = 2 * (-dx + dy);
    int x = startPoint.x;
    int y = startPoint.y;
    drawSquare78(x, y);
    while(y > finishPoint.y) {
        if(d < 0) {
            d += incrE;
            y -= thickness;
        } else {
            d += incrNE;
            x -= thickness;
            y -= thickness;
        }
        drawSquare78(x, y);
    }
}

void LineDrawer::drawSquare12(int x, int y) {
    #pragma omp parallel for
    for(int xx = x; xx < x + thickness; xx++) {
        #pragma omp parallel for
        for(int yy = y; yy < y + thickness; yy++) {
            canvas->setPixel(xx, yy, Color::Black);
        }
    }
}

void LineDrawer::drawSquare34(int x, int y) {
    #pragma omp parallel for
    for(int xx = x; xx > x - thickness; xx--) {
        #pragma omp parallel for
        for(int yy = y; yy < y + thickness; yy++) {
            canvas->setPixel(xx, yy, Color::Black);
        }
    }
}

void LineDrawer::drawSquare56(int x, int y) {
    #pragma omp parallel for
    for(int xx = x; xx < x + thickness; xx++) {
        #pragma omp parallel for
        for(int yy = y; yy > y - thickness; yy--) {
            canvas->setPixel(xx, yy, Color::Black);
        }
    }
}

void LineDrawer::drawSquare78(int x, int y) {
    #pragma omp parallel for
    for(int xx = x; xx > x - thickness; xx--) {
        #pragma omp parallel for
        for(int yy = y; yy > y - thickness; yy--) {
            canvas->setPixel(xx, yy, Color::Black);
        }
    }
}
