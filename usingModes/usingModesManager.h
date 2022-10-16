#pragma once

#include "usingMode.h"
#include "normalUsingMode.h"
#include "editUsingMode.h"
#include "../canvases/canvas.h"
#include <SFML/Graphics.hpp>
#include "../drawers/pointDrawer.h"
#include "../drawers/lineDrawer.h"
#include "../polygons/polygonsContainer.h"
#include "../touchDetectors/pointTouchDetector.h"
#include "../touchDetectors/edgeTouchDetector.h"

class UsingModesManager {
public:
    UsingModesManager(
        sf::Window* window,
        Canvas* canvas,
        PointDrawer* pointDrawer,
        LineDrawer* lineDrawer,
        PolygonsContainer* polygonsContainer,
        PointTouchDetector* pointTouchDetector,
        EdgeTouchDetector* edgeTouchDetector
    );
    ~UsingModesManager();
    void drawCurrentUsingMode();
    void updateCurrentUsingMode();

    enum class UsingModeType {
        normal,
        edit,
        relation
    };

    void setUsingMode(UsingModeType type);

private:
    UsingMode* usingMode;
    UsingModeType usingModeType;
    sf::Window* window;
    Canvas* canvas;
    PointDrawer* pointDrawer;
    LineDrawer* lineDrawer;
    PolygonsContainer* polygonsContainer;
    PointTouchDetector* pointTouchDetector;
    EdgeTouchDetector* edgeTouchDetector;
};
