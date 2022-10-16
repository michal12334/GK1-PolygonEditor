#include <SFML/Graphics.hpp>
#include "globalModules.h"
#include "buttons/button.h"
#include "panels/upperPanel.h"
#include "canvases/canvas.h"
#include "usingModes/editUsingMode.h"

int main() {
    GlobalModules globalModules;
    auto window = globalModules.getWindow();
    auto upperPanel = globalModules.getUpperPanel();
    auto canvas = globalModules.getCanvas();
    auto polygons = globalModules.getPolygonsContainer();
    auto usingModesManager = globalModules.getUsingModesManager();

    sf::Event event;
    while (window->isOpen()) {
        usingModesManager->updateCurrentUsingMode();
        upperPanel->update();

        window->clear();
        window->draw(*upperPanel);
        canvas->clear();
        polygons->draw();
        usingModesManager->drawCurrentUsingMode();
        canvas->updateTexture();
        window->draw(*canvas);
        window->display();

        while(window->pollEvent(event))
            if (event.type == sf::Event::Closed)
                window->close();
    }

    return 0;
}
