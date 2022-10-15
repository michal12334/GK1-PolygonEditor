#include "polygon.h"
#include <iostream>

using namespace sf;
using namespace std;

Polygon::Polygon(const vector<Vector2i>& points, PointDrawer* pointDrawer, LineDrawer* lineDrawer) {
    this->points = points;
    this->pointDrawer = pointDrawer;
    this->lineDrawer = lineDrawer;
}

void Polygon::draw() {
    for(int i = 0; i < points.size(); i++) {
        pointDrawer->draw(points[i]);
        lineDrawer->draw(points[i], points[(i + 1) % points.size()]);
    }
}

vector<Vector2i> Polygon::getPoints() const {
    return points;
}

void Polygon::updatePoint(int index, Vector2i newValue) {
    points[index] = newValue;
}
