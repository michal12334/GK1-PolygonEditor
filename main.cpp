#include <SFML/Graphics.hpp>
#include "globalModules.h"
#include "buttons/rectangleButton.h"
#include "panels/upperPanel.h"
#include "canvases/canvas.h"
#include <cstdlib>
#include <ctime>
#include "usingModes/editUsingMode.h"

int main() {
    srand(time(NULL));
    GlobalModules globalModules;
    auto window = globalModules.GetWindow();
    auto upperPanel = globalModules.getUpperPanel();
    auto canvas = globalModules.getCanvas();
    EditUsingMode editUsingMode(window, canvas, globalModules.getPointDrawer(), globalModules.getLineDrawer());

    sf::Event event;
    while (window->isOpen()) {
        canvas->setPixel(rand() % 1200, rand() % 860, sf::Color::Red);
        editUsingMode.update();

        canvas->updateTexture();
        window->clear();
        window->draw(*upperPanel);
        window->draw(*canvas);
        window->display();

        while(window->pollEvent(event))
            if (event.type == sf::Event::Closed)
                window->close();
    }

    return 0;
}
