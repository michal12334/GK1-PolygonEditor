#include "globalModules.h"
#include "usingModes/normalUsingMode.h"
#include "usingModes/editUsingMode.h"

using namespace sf;

GlobalModules::GlobalModules() {
    usingMode = new NormalUsingMode();
}

GlobalModules::~GlobalModules() {
    if(window != nullptr)
        delete window;

    if(usingMode != nullptr)
        delete usingMode;

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
}

RenderWindow* GlobalModules::GetWindow() {
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
        upperPanel = new UpperPanel(Vector2f(getWindowWidth(), 40));

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
        polygonsContainer = new PolygonsContainer(getLineDrawer(), getPointDrawer());

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

GlobalModules::UsingModeType GlobalModules::getUsingModeType() {
    return usingModeType;
}

void GlobalModules::setUsingMode(GlobalModules::UsingModeType usingModeType) {
    if(this->usingModeType == usingModeType)
        return;
    
    this->usingModeType = usingModeType;
    delete usingMode;
    switch(usingModeType) {
        case UsingModeType::normal:
            usingMode = new NormalUsingMode();
            break;

        case UsingModeType::edit:
            //usingMode = new EditUsingMode();
            break;
    }
}
