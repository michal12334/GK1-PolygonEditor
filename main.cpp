#include <SFML/Graphics.hpp>
#include "globalModules.h"
#include "buttons/rectangleButton.h"
#include "panels/upperPanel.h"

int main() {
    GlobalModules globalModules;
    auto window = globalModules.GetWindow();
    Button* button = new RectangleButton(sf::Vector2f(30, 30), sf::Vector2f(10, 400), sf::Color::Red);
    auto upperPanel = new UpperPanel(sf::Vector2f(globalModules.getWindowWidth(), 40));

    sf::Event event;
    while (window->isOpen()) {
        window->pollEvent(event);
        if (event.type == sf::Event::Closed) {
            window->close();
            break;
        }

        window->clear();
        window->draw(*button);
        window->draw(*upperPanel);
        window->display();
    }

    delete button;

    return 0;
}
