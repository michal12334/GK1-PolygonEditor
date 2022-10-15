#pragma once

#include "usingMode.h"
#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"
#include "../drawers/pointDrawer.h"
#include "../drawers/lineDrawer.h"
#include <vector>
#include "../polygons/polygonsContainer.h"
#include "polygonCreator.h"
#include "../touchDetectors/pointTouchDetector.h"
#include "../dragAndDroppers/pointDragAndDropper.h"
#include "../touchDetectors/edgeTouchDetector.h"
#include "../dragAndDroppers/edgeDragAndDropper.h"

class EditUsingMode : public UsingMode {
public:
    EditUsingMode(
        sf::Window* window,
        Canvas* canvas,
        PointDrawer* pointDrawer,
        LineDrawer* lineDrawer,
        PolygonsContainer* polygonsContainer,
        PointTouchDetector* pointTouchDetector,
        EdgeTouchDetector* edgeTouchDetector);
    ~EditUsingMode();
    virtual void update() override;
    void draw();

private:
    sf::Vector2i getMousePositionOnCanvas();
    bool isMouseOnCanvas(sf::Vector2i mousePositionOnCanvas);
    void updateHighlight(sf::Vector2i mousePositionOnCanvas);
    void doMouseLeftButtonAction(sf::Vector2i mousePositionOnCanvas);
    void doMouseRightButtonAction(sf::Vector2i mousePositionOnCanvas);
    void doDeleteButtonAction();

    sf::Window* window;
    Canvas* canvas;
    bool isMouseLeftButtonPressed = false;
    bool isMouseRightButtonPressed = false;
    bool isDeleteButtonPressed = false;
    PointDrawer* pointDrawer;
    LineDrawer* lineDrawer;
    bool isPolygonBeingDrawn = false;
    std::vector<sf::Vector2i> points;
    PolygonsContainer* polygonsContainer;
    PolygonCreator* polygonCreator;
    PointTouchDetector* pointTouchDetector;
    EdgeTouchDetector* edgeTouchDetector;
    TouchedPointData* touchedPointData = nullptr;
    PointDragAndDropper* pointDragAndDropper = nullptr;
    TouchedEdgeData* touchedEdgeData = nullptr;
    EdgeDragAndDropper* edgeDragAndDropper = nullptr;
};
