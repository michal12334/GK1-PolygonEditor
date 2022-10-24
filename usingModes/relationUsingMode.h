#pragma once

#include <SFML/Graphics.hpp>
#include "usingMode.h"
#include "../touchDetectors/edgeTouchDetector.h"
#include "../polygons/polygonsContainer.h"
#include "../textBoxes/textBox.h"

class RelationUsingMode : public UsingMode {
public:
    RelationUsingMode(
        sf::Window* window,
        Canvas* canvas,
        EdgeTouchDetector* edgeTouchDetector,
        PolygonsContainer* polygonsContainer
    );
    ~RelationUsingMode();
    virtual void update() override;
    virtual void draw() override;

private:
    sf::Vector2i getMousePositionOnCanvas();
    bool isMouseOnCanvas(sf::Vector2i mousePositionOnCanvas);

    bool isMouseLeftButtonPressed = false;
    bool isMouseRightButtonPressed = false;
    bool isEnterKeyPressed = false;

    sf::Window* window;
    Canvas* canvas;
    EdgeTouchDetector* edgeTouchDetector;
    PolygonsContainer* polygonsContainer;
    TextBox* textBox = nullptr;
    TouchedEdgeData* touchedEdgeData = nullptr;
};
