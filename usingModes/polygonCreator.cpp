#include "polygonCreator.h"

using namespace std;
using namespace sf;

PolygonCreator::PolygonCreator(PointDrawer* pointDrawer, LineDrawer* lineDrawer, Canvas* canvas, sf::Window* window) {
    this->pointDrawer = pointDrawer;
    this->lineDrawer = lineDrawer;
    this->canvas = canvas;
    this->window = window;
    end = false;
}

void PolygonCreator::update() {
    if(end)
        return;

    auto mousePositionOnCanvas = getMousePositionOnCanvas();

    if(points.size() >= 2 && isMouseOnFirstPoint(mousePositionOnCanvas))
        end = true;
    else
        points.push_back(mousePositionOnCanvas);
}

void PolygonCreator::draw() {
    if(points.size() == 0 || end)
        return;

    for(int i = 0; i < points.size(); i++) {
        pointDrawer->draw(points[i]);
        if(i != points.size() - 1) {
            lineDrawer->draw(points[i], points[i + 1]);
        }
    }

    auto mousePositionOnCanvas = getMousePositionOnCanvas();
    pointDrawer->draw(mousePositionOnCanvas);
    lineDrawer->draw(points[points.size() - 1], mousePositionOnCanvas);
}

bool PolygonCreator::isEnd() {
    return end;
}

void PolygonCreator::restart() {
    end = false;
    points.clear();
}

vector<Vector2i> PolygonCreator::getPoints() {
    return points;
}

bool PolygonCreator::isMouseOnFirstPoint(Vector2i mousePosition) {
    if(points.size() == 0)
        return false;

    auto firstPointPosition = points[0];
    int d2 = (mousePosition.x - firstPointPosition.x) * (mousePosition.x - firstPointPosition.x) +
        (mousePosition.y - firstPointPosition.y) * (mousePosition.y - firstPointPosition.y);

    return d2 <= 6*6;
}

Vector2i PolygonCreator::getMousePositionOnCanvas() {
    auto canvasPosition = canvas->getPosition();
    auto mousePosition = Mouse::getPosition(*window);
    return Vector2i(mousePosition.x - canvasPosition.x, mousePosition.y - canvasPosition.y);
}
