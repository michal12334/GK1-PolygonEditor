#include "usingModesManager.h"

UsingModesManager::UsingModesManager(
    sf::Window* window,
    Canvas* canvas,
    PointDrawer* pointDrawer,
    LineDrawer* lineDrawer,
    PolygonsContainer* polygonsContainer,
    PointTouchDetector* pointTouchDetector,
    EdgeTouchDetector* edgeTouchDetector,
    PolygonTouchDetector* polygonTouchDetector
)
{
    this->window = window;
    this->canvas = canvas;
    this->pointDrawer = pointDrawer;
    this->lineDrawer = lineDrawer;
    this->polygonsContainer = polygonsContainer;
    this->pointTouchDetector = pointTouchDetector;
    this->edgeTouchDetector = edgeTouchDetector;
    this->polygonTouchDetector = polygonTouchDetector;

    usingMode = new NormalUsingMode();
    usingModeType = UsingModeType::normal;
}

UsingModesManager::~UsingModesManager() {
    delete usingMode;
}

void UsingModesManager::drawCurrentUsingMode() {
    usingMode->draw();
}

void UsingModesManager::updateCurrentUsingMode() {
    usingMode->update();
}

void UsingModesManager::setUsingMode(UsingModeType type) {
    if(usingModeType == type)
        return;
    
    usingModeType = type;

    polygonsContainer->clearHighlight();
    polygonsContainer->clearSelection();

    switch(usingModeType) {
        case UsingModeType::normal:
            delete usingMode;
            usingMode = new NormalUsingMode();
            break;

        case UsingModeType::edit:
            delete usingMode;
            usingMode = new EditUsingMode(
                window,
                canvas,
                pointDrawer,
                lineDrawer,
                polygonsContainer,
                pointTouchDetector,
                edgeTouchDetector,
                polygonTouchDetector
            );
            break;

        case UsingModeType::relation:
            delete usingMode;
            usingMode = new RelationUsingMode(
                window,
                canvas,
                edgeTouchDetector,
                polygonsContainer
            );
            break;
    }
}
