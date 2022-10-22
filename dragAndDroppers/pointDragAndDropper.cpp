#include "pointDragAndDropper.h"
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

PointDragAndDropper::PointDragAndDropper(TouchedPointData* touchedPointData, LineDrawer* lineDrawer, PointDrawer* pointDrawer, PolygonsContainer *polygonsContainer, Vector2i mousePositionOnCanvas) {
    this->touchedPointData = touchedPointData;
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
    this->polygonsContainer = polygonsContainer;
    previousMousePosition = mousePositionOnCanvas;
    newPolygon = polygonsContainer->getPolygons()[touchedPointData->polygonIndex];
}

void PointDragAndDropper::update(Vector2i mousePositionOnCanvas) {
    auto delta = mousePositionOnCanvas - previousMousePosition;
    previousMousePosition = mousePositionOnCanvas;
    auto points = newPolygon.getPoints();
    vector<Vector2f> newPoints;
    for(int i = 0; i < points.size(); i++) {
        newPoints.push_back(Vector2f(points[i].x, points[i].y));
    }

    auto lengths = polygonsContainer->getLengthByPolygon(touchedPointData->polygonIndex);
    if(lengths.size() == newPoints.size()) {
        for(int i = 0; i < newPoints.size(); i++) {
            newPoints[i] += Vector2f(delta.x, delta.y);
        }
    } else {
        newPoints[touchedPointData->pointIndex] += Vector2f(delta.x, delta.y);
        int index = (touchedPointData->pointIndex - 1 + newPoints.size()) % newPoints.size();
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

        index = touchedPointData->pointIndex;
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

void PointDragAndDropper::draw() {
    newPolygon.draw(Color::Green);
}

void PointDragAndDropper::finish() {
    polygonsContainer->updatePolygon(touchedPointData->polygonIndex, newPolygon);
}

Vector2f PointDragAndDropper::getVersor(Vector2f a, Vector2f b) {
    auto result = a - b;
    float len = sqrt(result.x * result.x + result.y * result.y);
    return result / len;
}
