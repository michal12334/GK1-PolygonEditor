#include "polygonTouchDetector.h"
#include <cmath>

using namespace sf;
using namespace std;

PolygonTouchDetector::PolygonTouchDetector(PolygonsContainer* polygonsContainer) {
    this->polygonsContainer = polygonsContainer;
}

TouchedPolygonData* PolygonTouchDetector::getTouchedPolygon(Vector2i mousePosition) {
    auto polygons = polygonsContainer->getPolygons();
    for(int i = 0; i < polygons.size(); i++) {
        if(isPolygonTouched(polygons[i], mousePosition))
            return new TouchedPolygonData(i, polygons[i]);
    }

    return nullptr;
}

bool PolygonTouchDetector::isPolygonTouched(Polygon polygon, Vector2i mousePosition) {
    int left, right, up, bottom;
    getPolygonBorders(polygon, left, right, up, bottom);
    return mousePosition.x >= left && mousePosition.x <= right && mousePosition.y >= up && mousePosition.y <= bottom;
}

void PolygonTouchDetector::getPolygonBorders(Polygon polygon, int &left, int &right, int &up, int &bottom) {
    auto points = polygon.getPoints();
    left = right = points[0].x;
    up = bottom = points[0].y;
    for(int i = 1; i < points.size(); i++) {
        left = min(left, points[i].x);
        right = max(right, points[i].x);
        up = min(up, points[i].y);
        bottom = max(bottom, points[i].y);
    }
}
