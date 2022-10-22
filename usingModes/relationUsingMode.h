#pragma once

#include <SFML/Graphics.hpp>
#include "usingMode.h"
#include "../touchDetectors/edgeTouchDetector.h"
#include "../polygons/polygonsContainer.h"

class RelationUsingMode : public UsingMode {
public:
    RelationUsingMode(
        sf::Window* window,
        Canvas* canvas,
        EdgeTouchDetector* edgeTouchDetector,
        PolygonsContainer* polygonsContainer
    );
    virtual void update() override;
    virtual void draw() override;

private:
    sf::Vector2i getMousePositionOnCanvas();
    bool isMouseOnCanvas(sf::Vector2i mousePositionOnCanvas);

    sf::Window* window;
    Canvas* canvas;
    EdgeTouchDetector* edgeTouchDetector;
    PolygonsContainer* polygonsContainer;
};
