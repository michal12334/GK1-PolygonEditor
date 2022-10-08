#include "upperPanel.h"

using namespace sf;

UpperPanel::UpperPanel(Vector2f size, Vector2f position) {
    this->size = size;
    this->position = position;
    color = Color::Cyan;
    rectangle.setSize(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(color);

    normalModeButton = new RectangleButton(Vector2f(size.y, size.y), Vector2f(0, 0), Color::Red);
    polygonEditModeButton = new RectangleButton(Vector2f(size.y, size.y), Vector2f(0, 0), Color::Red);
    relationAddModeButton = new RectangleButton(Vector2f(size.y, size.y), Vector2f(0, 0), Color::Red);

    setPadding(5.0f);
}

UpperPanel::~UpperPanel() {
    delete normalModeButton;
    delete polygonEditModeButton;
    delete relationAddModeButton;
}

void UpperPanel::setPadding(float padding) {
    this->padding = padding;
    int buttonSizeDimension = size.y - 2 * padding;
    Vector2f buttonSize = Vector2f(buttonSizeDimension, buttonSizeDimension);
    normalModeButton->setSize(buttonSize);
    polygonEditModeButton->setSize(buttonSize);
    relationAddModeButton->setSize(buttonSize);
    normalModeButton->setPosition(Vector2f(padding, padding));
    polygonEditModeButton->setPosition(Vector2f(buttonSize.x + 2 * padding, padding));
    relationAddModeButton->setPosition(Vector2f(2 * buttonSize.x + 3 * padding, padding));
}

void UpperPanel::draw(RenderTarget &target, RenderStates states) const {
    target.draw(rectangle, states);
    target.draw(*normalModeButton, states);
    target.draw(*polygonEditModeButton, states);
    target.draw(*relationAddModeButton, states);
}
