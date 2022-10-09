#include <SFML/Graphics.hpp>
#include "globalModules.h"
#include "buttons/rectangleButton.h"
#include "panels/upperPanel.h"
#include "canvases/canvas.h"
#include "usingModes/editUsingMode.h"

int main() {
    GlobalModules globalModules;
    auto window = globalModules.GetWindow();
    auto upperPanel = globalModules.getUpperPanel();
    auto canvas = globalModules.getCanvas();
    auto polygons = globalModules.getPolygonsContainer();
    EditUsingMode editUsingMode(window, canvas, globalModules.getPointDrawer(), globalModules.getLineDrawer(), globalModules.getPolygonsContainer());

    sf::Event event;
    while (window->isOpen()) {
        editUsingMode.update();

        window->clear();
        window->draw(*upperPanel);
        canvas->clear();
        polygons->draw();
        editUsingMode.draw();
        canvas->updateTexture();
        window->draw(*canvas);
        window->display();

        while(window->pollEvent(event))
            if (event.type == sf::Event::Closed)
                window->close();
    }

    return 0;
}
