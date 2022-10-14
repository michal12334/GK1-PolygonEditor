#pragma once

#include "../polygons/polygon.h"

struct TouchedPointData {
    TouchedPointData(int polygonIndex, int pointIndex, Polygon polygon) 
    : polygonIndex(pointIndex), pointIndex(pointIndex), polygon(polygon) {}

    int polygonIndex;
    int pointIndex;
    Polygon polygon;
};
