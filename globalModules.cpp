#include "globalModules.h"

using namespace sf;

GlobalModules::~GlobalModules() {
    if(window != nullptr)
        delete window;

    if(usingMode != nullptr)
        delete usingMode;
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

GlobalModules::UsingModeType GlobalModules::getUsingModeType() {
    return usingModeType;
}

void GlobalModules::setUsingMode(GlobalModules::UsingModeType usingModeType) {
    this->usingModeType = usingModeType;
}
