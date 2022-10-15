#include "upperPanel.h"

using namespace sf;

UpperPanel::UpperPanel(Vector2f size, Vector2f position, float padding) {
    this->size = size;
    this->position = position;
    color = Color::Cyan;
    rectangle.setSize(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(color);

    int buttonSizeDimension = size.y - 2 * padding;
    Vector2f buttonSize = Vector2f(buttonSizeDimension, buttonSizeDimension);

    normalModeButton = new Button(buttonSize, Vector2f(padding, padding), 5);
    polygonEditModeButton = new Button(buttonSize, Vector2f(buttonSize.x + 2 * padding, padding), 5);
    relationAddModeButton = new Button(buttonSize, Vector2f(2 * buttonSize.x + 3 * padding, padding), 5);

    normalModeButton->setActive(true);
}

UpperPanel::~UpperPanel() {
    delete normalModeButton;
    delete polygonEditModeButton;
    delete relationAddModeButton;
}

void UpperPanel::draw(RenderTarget &target, RenderStates states) const {
    target.draw(rectangle, states);
    target.draw(*normalModeButton, states);
    target.draw(*polygonEditModeButton, states);
    target.draw(*relationAddModeButton, states);
}
