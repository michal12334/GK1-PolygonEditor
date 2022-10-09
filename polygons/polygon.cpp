#include "polygon.h"
#include "../drawers/lineDrawer.h"
#include "../drawers/pointDrawer.h"

using namespace sf;
using namespace std;

Polygon::Polygon(const vector<Vector2i>& points) {
    this->points = points;
}

void Polygon::draw(Canvas* canvas) {
    PointDrawer pointDrawer(5);
    LineDrawer lineDrawer(2);
    for(int i = 0; i < points.size(); i++) {
        pointDrawer.draw(canvas, points[0]);
        lineDrawer.draw(canvas, points[i], points[(i + 1) % points.size()]);
    }
}
