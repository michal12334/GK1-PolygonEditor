#include "polygonsContainer.h"

using namespace sf;
using namespace std;

PolygonsContainer::PolygonsContainer(LineDrawer* lineDrawer, PointDrawer* pointDrawer) {
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
}

void PolygonsContainer::addPolygon(Polygon polygon) {
    polygons.push_back(polygon);
}

void PolygonsContainer::addPolygon(vector<Vector2i> points) {
    addPolygon(Polygon(points, pointDrawer, lineDrawer));
}

void PolygonsContainer::draw() {
    for(auto& p : polygons) {
        p.draw();
    }
}

vector<Polygon> PolygonsContainer::getPolygons() {
    return polygons;
}
