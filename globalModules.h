#pragma once

#include <SFML/Graphics.hpp>
#include "usingModes/usingMode.h"

class GlobalModules {
public:
    GlobalModules();
    ~GlobalModules();
    sf::RenderWindow* GetWindow();
    int getWindowWidth();

    enum class UsingModeType {
        normal,
        edit,
        relation
    };

    UsingModeType getUsingModeType();
    void setUsingMode(UsingModeType usingModeType);

private:
    sf::RenderWindow* window = nullptr;
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 900;

    UsingModeType usingModeType = UsingModeType::normal;
    UsingMode* usingMode = nullptr;
};
