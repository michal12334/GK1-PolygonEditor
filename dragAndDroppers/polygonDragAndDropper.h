#pragma once

#include <SFML/Graphics.hpp>
#include "../drawers/lineDrawer.h"
#include "../drawers/pointDrawer.h"
#include "../polygons/polygonsContainer.h"
#include "../touchDetectors/touchedPolygonData.h"
#include <vector>

class PolygonDragAndDropper {
public:
    PolygonDragAndDropper(
        TouchedPolygonData* touchedPolygonData,
        LineDrawer* lineDrawer,
        PointDrawer* pointDrawer,
        PolygonsContainer *polygonsContainer,
        sf::Vector2i mousePosition
    );
    void update(sf::Vector2i mousePosition);
    void draw();
    void finish();

private:
    TouchedPolygonData* touchedPolygonData;
    LineDrawer* lineDrawer;
    PointDrawer* pointDrawer;
    PolygonsContainer *polygonsContainer;

    sf::Vector2i previousMousePosition;
    std::vector<sf::Vector2i> newPoints;
};
