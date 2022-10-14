#pragma once

#include "../polygons/polygonsContainer.h"
#include "touchedPointData.h"
#include <SFML/Graphics.hpp>

class PointTouchDetector {
public:
    PointTouchDetector(PolygonsContainer* polygonsContainer);
    TouchedPointData* getTouchedPoint(sf::Vector2i mousePosition);

private:
    bool isPointTouched(sf::Vector2i point, sf::Vector2i mousePosition);

    PolygonsContainer* polygonsContainer;
};
