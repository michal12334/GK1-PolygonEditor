#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../canvases/canvas.h"
#include <vector>

class TextBox {
public:
    TextBox(float startLen, sf::Vector2f position, unsigned int size);
    ~TextBox();
    void update();
    void draw(Canvas* canvas);
    float getValue();

private:
    const float TIME = 0.5f;
    const float SPEED = 2.0f;
    float time = 0.0f;
    bool isVisible = false;

    sf::Font font;
    sf::Text* text;
    std::string str;

    struct Key {
        Key(sf::Keyboard::Key key, char charactedToAdd)
        : key(key), charactedToAdd(charactedToAdd) {}

        sf::Keyboard::Key key;
        bool isPressed = false;
        char charactedToAdd;
    };
    std::vector<Key> keys;

    float string2float(std::string str);
    std::string float2string(float value);
};
