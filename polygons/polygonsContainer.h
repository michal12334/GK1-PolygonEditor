#pragma once

#include "polygon.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "../drawers/lineDrawer.h"
#include "../drawers/pointDrawer.h"
#include "../touchDetectors/touchedEdgeData.h"
#include "../touchDetectors/touchedPointData.h"
#include "../touchDetectors/touchedPolygonData.h"
#include <string>
#include "../relations/edgeLength.h"

class PolygonsContainer {
public:
    PolygonsContainer(LineDrawer* lineDrawer, PointDrawer* pointDrawer, Canvas* canvas);
    void addPolygon(Polygon polygon);
    void addPolygon(std::vector<sf::Vector2i> points);
    void draw();
    std::vector<Polygon> getPolygons();
    void updatePolygon(int polygonIndex, int pointIndex, sf::Vector2i newPointValue);
    void updatePolygon(int polygonIndex, Polygon newPolygonValue);
    void setHighlighten(TouchedEdgeData* touchedEdgeData);
    void setHighlighten(TouchedPointData* touchedPointData);
    void setHighlighten(TouchedPolygonData* touchedPolygonData);
    void clearHighlight();
    bool isEdgeHighlighten();
    void addPointOnHighlightenEdge();
    void setSelection(TouchedEdgeData* touchedEdgeData);
    void setSelection(TouchedPointData* touchedPointData);
    void setSelection(TouchedPolygonData* touchedPolygonData);
    void clearSelection();
    void deleteSelected();
    bool isSomethingSelected();
    void setEdgeLength(TouchedEdgeData* touchedEdgeData, float len);
    void setEdgeLength(TouchedEdgeData* touchedEdgeData);
    std::vector<EdgeLength> getLengthByPolygon(int polygonIndex);
    void removeEdgeLength(TouchedEdgeData* touchedEdgeData);
    void removeEdgeLength(int polygonIndex, int edgeIndex);
    void removeEdgeLengthsByPolygon(int polygonIndex);

private:
    std::vector<Polygon> polygons;
    LineDrawer* lineDrawer;
    PointDrawer* pointDrawer;
    Canvas* canvas;

    int highlightenPolygonIndex;
    int highlightenPointIndex;
    int highlightenEdgeIndex;

    int selectedPolygonIndex;
    int selectedPointIndex;
    int selectedEdgeIndex;

    std::vector<EdgeLength> lengths;
    void drawLen(EdgeLength edgeLength);
    sf::Font font;

    template<typename T>
    std::string numberToString(T num);
    sf::Vector2f getVersor(sf::Vector2f a, sf::Vector2f b);
};
