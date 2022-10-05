#include <SFML/Graphics.hpp>
#include "globalModules.h"

int main() {
    GlobalModules globalModules;
    auto& window = *globalModules.GetWindow();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}