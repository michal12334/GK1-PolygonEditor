#pragma once

#include "usingMode.h"
#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"
#include "../drawers/pointDrawer.h"
#include "../drawers/lineDrawer.h"
#include <vector>
#include "../polygons/polygonsContainer.h"
#include "polygonCreator.h"

class EditUsingMode : public UsingMode {
public:
    EditUsingMode(sf::Window* window, Canvas* canvas, PointDrawer* pointDrawer, LineDrawer* lineDrawer, PolygonsContainer* polygonsContainer);
    ~EditUsingMode();
    virtual void update() override;
    void draw();

private:
    bool isMouseOnFirstPoint(sf::Vector2i mousePosition);
    sf::Vector2i getMousePositionOnCanvas();
    bool isMouseOnCanvas(sf::Vector2i mousePositionOnCanvas);

    sf::Window* window;
    Canvas* canvas;
    bool isMouseLeftButtonPressed = false;
    PointDrawer* pointDrawer;
    LineDrawer* lineDrawer;
    bool isPolygonBeingDrawn = false;
    std::vector<sf::Vector2i> points;
    PolygonsContainer* polygonsContainer;

    PolygonCreator* polygonCreator;
};
