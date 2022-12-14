#pragma once

#include <SFML/Graphics.hpp>
#include "../drawers/lineDrawer.h"
#include "../drawers/pointDrawer.h"
#include "../polygons/polygonsContainer.h"
#include "../touchDetectors/touchedEdgeData.h"

class EdgeDragAndDropper {
public:
    EdgeDragAndDropper(
        TouchedEdgeData* touchedEdgeData,
        LineDrawer* lineDrawer,
        PointDrawer* pointDrawer,
        PolygonsContainer *polygonsContainer,
        sf::Vector2i mousePosition
    );
    void update(sf::Vector2i mousePosition);
    void draw();
    void finish();

private:
    TouchedEdgeData* touchedEdgeData;
    LineDrawer* lineDrawer;
    PointDrawer* pointDrawer;
    PolygonsContainer *polygonsContainer;

    sf::Vector2i previousMousePosition;
    Polygon newPolygon;

    sf::Vector2f getVersor(sf::Vector2f a, sf::Vector2f b);
};
