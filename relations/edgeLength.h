#pragma once

struct EdgeLength {
    EdgeLength(int polygonIndex, int edgeIndex, float len)
    : polygonIndex(polygonIndex), edgeIndex(edgeIndex), len(len) {}

    int polygonIndex;
    int edgeIndex;
    float len;
};
