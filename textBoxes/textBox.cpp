#include "textBox.h"
#include <sstream>

using namespace std;
using namespace sf;

TextBox::TextBox(float startLen, Vector2f position, unsigned int size) {
    font.loadFromFile("fonts/FuzzyBubbles-Regular.ttf");
    text->setFont(font);
    text->setPosition(position);
    text->setCharacterSize(size);
    text->setFillColor(Color::Black);
    keys.push_back(Key(Keyboard::Key::Num0, '0'));
    keys.push_back(Key(Keyboard::Key::Num1, '1'));
    keys.push_back(Key(Keyboard::Key::Num2, '2'));
    keys.push_back(Key(Keyboard::Key::Num3, '3'));
    keys.push_back(Key(Keyboard::Key::Num4, '4'));
    keys.push_back(Key(Keyboard::Key::Num5, '5'));
    keys.push_back(Key(Keyboard::Key::Num6, '6'));
    keys.push_back(Key(Keyboard::Key::Num7, '7'));
    keys.push_back(Key(Keyboard::Key::Num8, '8'));
    keys.push_back(Key(Keyboard::Key::Num9, '9'));
    keys.push_back(Key(Keyboard::Key::Period, '.'));
    keys.push_back(Key(Keyboard::Key::Subtract, '-'));
    keys.push_back(Key(Keyboard::Key::BackSpace, '\0'));
}

TextBox::~TextBox() {
    delete text;
}

void TextBox::update() {
    text->setString(str + "|");
    for(int i = 0; i < keys.size(); i++) {
        if(!keys[i].isPressed && Keyboard::isKeyPressed(keys[i].key)) {
            keys[i].isPressed = true;
            if(keys[i].charactedToAdd != '\0') {
                str += keys[i].charactedToAdd;
            } else if(str.size() > 0) {
                str.erase(str.begin() + str.size() - 1);
            }
        } else if(!Keyboard::isKeyPressed(keys[i].key)) {
            keys[i].isPressed = false;
        }
    }
}

void TextBox::draw(Canvas* canvas) {
    canvas->drawNative(text);
}

float TextBox::getValue() {
    return string2float(str);
}

float TextBox::string2float(string str) {
    istringstream stream(str);
    float result;
    stream >> result;
    return result;
}
