#include "edgeTouchDetector.h"
#include <cmath>

using namespace sf;
using namespace std;

EdgeTouchDetector::EdgeTouchDetector(PolygonsContainer* polygonsContainer) {
    this->polygonsContainer = polygonsContainer;
}

TouchedEdgeData* EdgeTouchDetector::getTouchedEdge(Vector2i mousePosition) {
    auto polygons = polygonsContainer->getPolygons();
    for(int i = 0; i < polygons.size(); i++) {
        auto points = polygons[i].getPoints();
        for(int j = 0; j < points.size(); j++) {
            if(isEdgeTouched(points[j], points[(j + 1) % points.size()], mousePosition)) {
                return new TouchedEdgeData(i, j, (j + 1) % points.size(), polygons[i]);
            }
        }
    }

    return nullptr;
}

bool EdgeTouchDetector::isEdgeTouched(Vector2i startPoint, Vector2i finishPoint, Vector2i mousePosition) {
    int len2 = getDisctance2(startPoint, finishPoint);
    int d2_1 = getDisctance2(startPoint, mousePosition);
    int d2_2 = getDisctance2(finishPoint, mousePosition);

    auto len = sqrt(len2);
    auto d1 = sqrt(d2_1);
    auto d2 = sqrt(d2_2);

    return d1 + d2 - len <= 3;
}

int EdgeTouchDetector::getDisctance2(sf::Vector2i a, sf::Vector2i b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
