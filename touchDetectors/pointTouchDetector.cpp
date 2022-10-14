#include "pointTouchDetector.h"

using namespace sf;

PointTouchDetector::PointTouchDetector(PolygonsContainer* polygonsContainer) {
    this->polygonsContainer = polygonsContainer;
}

TouchedPointData* PointTouchDetector::getTouchedPoint(sf::Vector2i mousePosition) {
    auto polygons = polygonsContainer->getPolygons();
    for(int i = 0; i < polygons.size(); i++) {
        auto points = polygons[i].getPoints();
        for(int j = 0; j < points.size(); j++) {
            if(isPointTouched(points[j], mousePosition)) {
                return new TouchedPointData(i, j, polygons[i]);
            }
        }
    }

    return nullptr;
}

bool PointTouchDetector::isPointTouched(Vector2i point, Vector2i mousePosition) {
    int d2 = (point.x - mousePosition.x) * (point.x - mousePosition.x) +
        (point.y - mousePosition.y) * (point.y - mousePosition.y);
    
    return d2 <= 6*6;
}
