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
    auto upperPanel = new UpperPanel(sf::Vector2f(globalModules.getWindowWidth(), 40));
    auto canvas = new Canvas(sf::Vector2i(1200, 860), sf::Vector2f(0, 40));
    EditUsingMode editUsingMode(window, canvas);

    sf::Event event;
    while (window->isOpen()) {
        window->pollEvent(event);
        if (event.type == sf::Event::Closed) {
            window->close();
            break;
        }

        canvas->setPixel(rand() % 1200, rand() % 860, sf::Color::Red);
        editUsingMode.update();

        canvas->updateTexture();
        window->clear();
        window->draw(*upperPanel);
        window->draw(*canvas);
        window->display();
    }

    return 0;
}
