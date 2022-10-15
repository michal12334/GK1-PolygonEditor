#pragma once

#include <SFML/Graphics.hpp>
#include "../touchDetectors/touchedPointData.h"
#include "../drawers/lineDrawer.h"
#include "../drawers/pointDrawer.h"
#include "../polygons/polygonsContainer.h"

class PointDragAndDropper {
public:
    PointDragAndDropper(TouchedPointData* touchedPointData, LineDrawer* lineDrawer, PointDrawer* pointDrawer, PolygonsContainer *polygonsContainer, sf::Vector2i mousePositionOnCanvas);
    void update(sf::Vector2i mousePositionOnCanvas);
    void draw();
    void finish();

private:
    TouchedPointData* touchedPointData;
    LineDrawer* lineDrawer;
    PointDrawer* pointDrawer;
    PolygonsContainer *polygonsContainer;

    sf::Vector2i newPointPosition;
};
