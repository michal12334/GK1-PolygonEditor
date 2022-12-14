#include "polygon.h"
#include <cmath>

using namespace sf;
using namespace std;

Polygon::Polygon(const vector<Vector2i>& points, PointDrawer* pointDrawer, LineDrawer* lineDrawer) {
    this->points = points;
    this->pointDrawer = pointDrawer;
    this->lineDrawer = lineDrawer;
}

void Polygon::draw(Color color) {
    for(int i = 0; i < points.size(); i++) {
        pointDrawer->draw(points[i], color);
        lineDrawer->draw(points[i], points[(i + 1) % points.size()], color);
    }
}

void Polygon::drawWithHighlihtenPoint(int pointIndex, sf::Color color) {
    for(int i = 0; i < points.size(); i++) {
        if(i == pointIndex)
            pointDrawer->draw(points[i], color);
        else
            pointDrawer->draw(points[i]);
        lineDrawer->draw(points[i], points[(i + 1) % points.size()]);
    }
}

void Polygon::drawWithHighlihtenEdge(int edgeIndex, sf::Color color) {
    for(int i = 0; i < points.size(); i++) {
        pointDrawer->draw(points[i]);
        if(i == edgeIndex)
            lineDrawer->draw(points[i], points[(i + 1) % points.size()], color);
        else
            lineDrawer->draw(points[i], points[(i + 1) % points.size()]);
    }
}

vector<Vector2i> Polygon::getPoints() const {
    return points;
}

void Polygon::updatePoint(int index, Vector2i newValue) {
    points[index] = newValue;
}

void Polygon::addPointOnEdge(int edgeIndex) {
    auto prev = points[edgeIndex];
    auto next = points[(edgeIndex + 1) % points.size()];
    points.insert(points.begin() + edgeIndex + 1, (prev + next) / 2);
}

void Polygon::deletePoint(int index) {
    points.erase(points.begin() + index);
}

float Polygon::getEdgeLength(int edgeIndex) {
    auto a = points[edgeIndex];
    auto b = points[(edgeIndex + 1) % points.size()];
    return sqrt(
        (a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y)
    );
}
