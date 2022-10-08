#include "globalModules.h"

using namespace sf;

GlobalModules::~GlobalModules() {
    if(window != nullptr)
        delete window;
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

GlobalModules::UsingMode GlobalModules::getUsingMode() {
    return usingMode;
}

void GlobalModules::setUsingMode(GlobalModules::UsingMode usingMode) {
    this->usingMode = usingMode;
}
