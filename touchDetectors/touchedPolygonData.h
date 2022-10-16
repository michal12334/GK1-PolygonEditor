#pragma once

#include "../polygons/polygon.h"

struct TouchedPolygonData {
    TouchedPolygonData(int polygonIndex, Polygon polygon)
    :polygonIndex(polygonIndex), polygon(polygon) {}

    int polygonIndex;
    Polygon polygon;
};
