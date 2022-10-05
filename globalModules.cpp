#include "globalModules.h"

using namespace sf;

RenderWindow* GlobalModules::GetWindow() {
    if(window == nullptr) {
        window = new RenderWindow(sf::VideoMode(1200, 900), "title");
    }
    return window;
}
