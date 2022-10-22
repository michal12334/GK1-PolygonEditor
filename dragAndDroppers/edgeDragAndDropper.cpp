#include "edgeDragAndDropper.h"
#include <cmath>

using namespace sf;
using namespace std;

EdgeDragAndDropper::EdgeDragAndDropper(
    TouchedEdgeData* touchedEdgeData,
    LineDrawer* lineDrawer,
    PointDrawer* pointDrawer,
    PolygonsContainer *polygonsContainer,
    Vector2i mousePosition
) {
    this->touchedEdgeData = touchedEdgeData;
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
    this->polygonsContainer = polygonsContainer;
    previousMousePosition = mousePosition;
    newPolygon = polygonsContainer->getPolygons()[touchedEdgeData->polygonIndex];
}

void EdgeDragAndDropper::update(Vector2i mousePosition) {
    auto delta = mousePosition - previousMousePosition;
    previousMousePosition = mousePosition;
    auto points = newPolygon.getPoints();
    vector<Vector2f> newPoints;
    for(int i = 0; i < points.size(); i++) {
        newPoints.push_back(Vector2f(points[i].x, points[i].y));
    }

    auto lengths = polygonsContainer->getLengthByPolygon(touchedEdgeData->polygonIndex);
    if(lengths.size() == newPoints.size()) {
        for(int i = 0; i < newPoints.size(); i++) {
            newPoints[i] += Vector2f(delta.x, delta.y);
        }
    } else {
        newPoints[touchedEdgeData->startPointIndex] += Vector2f(delta.x, delta.y);
        newPoints[touchedEdgeData->finishPointIndex] += Vector2f(delta.x, delta.y);
        int index = (touchedEdgeData->startPointIndex - 1 + newPoints.size()) % newPoints.size();
        while(true) {
            float len = -1;
            for(int i = 0; i < lengths.size(); i++) {
                if(lengths[i].edgeIndex == index) {
                    len = lengths[i].len;
                    break;
                }
            }
            if(len == -1) {
                break;
            }
            auto versor = getVersor(newPoints[index], newPoints[(index + 1) % points.size()]);
            auto vector = versor * len;
            newPoints[index] = newPoints[(index + 1) % points.size()] + vector;

            index = (index - 1 + newPoints.size()) % newPoints.size();
        }

        index = touchedEdgeData->finishPointIndex;
        while(true) {
            float len = -1;
            for(int i = 0; i < lengths.size(); i++) {
                if(lengths[i].edgeIndex == index) {
                    len = lengths[i].len;
                    break;
                }
            }
            if(len == -1) {
                break;
            }
            auto versor = getVersor(newPoints[(index + 1) % points.size()], newPoints[index]);
            auto vector = versor * len;
            newPoints[(index + 1) % points.size()] = newPoints[index] + vector;

            index = (index + 1) % newPoints.size();
        }
    }

    for(int i = 0; i < newPoints.size(); i++) {
        newPolygon.updatePoint(i, Vector2i(newPoints[i].x, newPoints[i].y));
    }
}

void EdgeDragAndDropper::draw() {
    newPolygon.draw(Color::Green);
}

void EdgeDragAndDropper::finish() {
    polygonsContainer->updatePolygon(touchedEdgeData->polygonIndex, newPolygon);
}

Vector2f EdgeDragAndDropper::getVersor(Vector2f a, Vector2f b) {
    auto result = a - b;
    float len = sqrt(result.x * result.x + result.y * result.y);
    return result / len;
}
