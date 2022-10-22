#include "globalModules.h"
#include "usingModes/normalUsingMode.h"
#include "usingModes/editUsingMode.h"

using namespace sf;

GlobalModules::GlobalModules() {
}

GlobalModules::~GlobalModules() {
    if(window != nullptr)
        delete window;

    if(upperPanel != nullptr)
        delete upperPanel;

    if(canvas != nullptr)
        delete canvas;

    if(lineDrawer != nullptr)
        delete lineDrawer;

    if(pointDrawer != nullptr)
        delete pointDrawer;

    if(polygonsContainer != nullptr)
        delete polygonsContainer;

    if(pointTouchDetector != nullptr)
        delete pointTouchDetector;

    if(edgeTouchDetector != nullptr)
        delete edgeTouchDetector;

    if(usingModesManager != nullptr)
        delete usingModesManager;

    if(polygonTouchDetector != nullptr)
        delete polygonTouchDetector;
}

RenderWindow* GlobalModules::getWindow() {
    if(window == nullptr) {
        window = new RenderWindow(sf::VideoMode(1200, 900), "title");
    }
    return window;
}

int GlobalModules::getWindowWidth() {
    return WINDOW_WIDTH;
}

UpperPanel* GlobalModules::getUpperPanel() {
    if(upperPanel == nullptr)
        upperPanel = new UpperPanel(getWindow(), getUsingModesManager(), Vector2f(getWindowWidth(), 40));

    return upperPanel;
}

Canvas* GlobalModules::getCanvas() {
    if(canvas == nullptr)
        canvas = new Canvas(sf::Vector2i(1200, 860), sf::Vector2f(0, 40));

    return canvas;
}

LineDrawer* GlobalModules::getLineDrawer() {
    if(lineDrawer == nullptr)
        lineDrawer = new LineDrawer(getCanvas());

    return lineDrawer;
}

PointDrawer* GlobalModules::getPointDrawer() {
    if(pointDrawer == nullptr)
        pointDrawer = new PointDrawer(getCanvas(), 5);

    return pointDrawer;
}

PolygonsContainer* GlobalModules::getPolygonsContainer() {
    if(polygonsContainer == nullptr)
        polygonsContainer = new PolygonsContainer(getLineDrawer(), getPointDrawer(), getCanvas());

    return polygonsContainer;
}

PointTouchDetector* GlobalModules::getPointTouchDetector() {
    if(pointTouchDetector == nullptr)
        pointTouchDetector = new PointTouchDetector(getPolygonsContainer());

    return pointTouchDetector;
}

EdgeTouchDetector* GlobalModules::getEdgeTouchDetector() {
    if(edgeTouchDetector == nullptr)
        edgeTouchDetector = new EdgeTouchDetector(getPolygonsContainer());

    return edgeTouchDetector;
}

UsingModesManager* GlobalModules::getUsingModesManager() {
    if(usingModesManager == nullptr)
        usingModesManager = new UsingModesManager(
            getWindow(),
            getCanvas(),
            getPointDrawer(),
            getLineDrawer(),
            getPolygonsContainer(),
            getPointTouchDetector(),
            getEdgeTouchDetector(),
            getPolygonTouchDetector()
        );
    
    return usingModesManager;
}

PolygonTouchDetector* GlobalModules::getPolygonTouchDetector() {
    if(polygonTouchDetector == nullptr)
        polygonTouchDetector = new PolygonTouchDetector(getPolygonsContainer());
    
    return polygonTouchDetector;
}
