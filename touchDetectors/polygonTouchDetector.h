#pragma once

#include "../polygons/polygonsContainer.h"
#include "touchedPolygonData.h"
#include <SFML/Graphics.hpp>

class PolygonTouchDetector {
public:
    PolygonTouchDetector(PolygonsContainer* polygonsContainer);
    TouchedPolygonData* getTouchedPolygon(sf::Vector2i mousePosition);

private:
    bool isPolygonTouched(Polygon polygon, sf::Vector2i mousePosition);
    void getPolygonBorders(Polygon polygon, int &left, int &right, int &up, int &bottom);

    PolygonsContainer* polygonsContainer;
};
