#pragma once

#include <SFML/Graphics.hpp>
#include "usingModes/usingMode.h"
#include "panels/upperPanel.h"
#include "canvases/canvas.h"
#include "drawers/lineDrawer.h"
#include "drawers/pointDrawer.h"
#include "polygons/polygonsContainer.h"
#include "touchDetectors/pointTouchDetector.h"
#include "touchDetectors/edgeTouchDetector.h"
#include "usingModes/usingModesManager.h"

class GlobalModules {
public:
    GlobalModules();
    ~GlobalModules();
    sf::RenderWindow* getWindow();
    int getWindowWidth();
    UpperPanel* getUpperPanel();
    Canvas* getCanvas();
    LineDrawer* getLineDrawer();
    PointDrawer* getPointDrawer();
    PolygonsContainer* getPolygonsContainer();
    PointTouchDetector* getPointTouchDetector();
    EdgeTouchDetector* getEdgeTouchDetector();
    UsingModesManager* getUsingModesManager();

private:
    sf::RenderWindow* window = nullptr;
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 900;

    UpperPanel* upperPanel = nullptr;
    Canvas* canvas = nullptr;
    LineDrawer* lineDrawer = nullptr;
    PointDrawer* pointDrawer = nullptr;
    PolygonsContainer* polygonsContainer = nullptr;
    PointTouchDetector* pointTouchDetector = nullptr;
    EdgeTouchDetector* edgeTouchDetector = nullptr;
    UsingModesManager* usingModesManager = nullptr;
};
