#pragma once

#include <SFML/Graphics.hpp>
#include "../polygons/polygonsContainer.h"
#include "touchedEdgeData.h"

class EdgeTouchDetector {
public:
    EdgeTouchDetector(PolygonsContainer* polygonsContainer);
    TouchedEdgeData* getTouchedEdge(sf::Vector2i mousePosition);

private:
    bool isEdgeTouched(sf::Vector2i startPoint, sf::Vector2i finishPoint, sf::Vector2i mousePosition);
    int getDisctance2(sf::Vector2i a, sf::Vector2i b);

    PolygonsContainer* polygonsContainer;
};
