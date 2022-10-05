#pragma once

#include <SFML/Graphics.hpp>

class GlobalModules {
public:
    sf::RenderWindow* GetWindow();

private:
    sf::RenderWindow* window;
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 900;
};
