#pragma once

#include <SFML/Graphics.hpp>

class GlobalModules {
public:
    ~GlobalModules();
    sf::RenderWindow* GetWindow();
    int getWindowWidth();

private:
    sf::RenderWindow* window = nullptr;
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 900;
};
