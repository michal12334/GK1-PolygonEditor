#pragma once

#include "../polygons/polygon.h"

struct TouchedEdgeData {
    TouchedEdgeData(int polygonIndex, int startPointIndex, int finishPointIndex, Polygon polygon)
    : polygonIndex(polygonIndex), startPointIndex(startPointIndex), finishPointIndex(finishPointIndex), polygon(polygon) {}

    int polygonIndex;
    int startPointIndex;
    int finishPointIndex;
    Polygon polygon;
};
