#include "upperPanel.h"

using namespace sf;

UpperPanel::UpperPanel(
    Window* window,
    UsingModesManager* usingModesManager,
    Vector2f size,
    Vector2f position,
    float padding
) {
    this->window = window;
    this->usingModesManager = usingModesManager;
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
    normalModeButton->setText("N", Vector2f(8, 2), 20);
    polygonEditModeButton->setText("E", Vector2f(10, 2), 20);
    relationAddModeButton->setText("R", Vector2f(9, 2), 20);

    normalModeButton->setActive(true);
}

UpperPanel::~UpperPanel() {
    delete normalModeButton;
    delete polygonEditModeButton;
    delete relationAddModeButton;
}

void UpperPanel::update() {
    if(Mouse::isButtonPressed(Mouse::Button::Left)) {
        if(!isMouseLeftButtonPressed) {
            if(normalModeButton->isTouched(window) && !normalModeButton->isActive()) {
                normalModeButton->setActive(true);
                polygonEditModeButton->setActive(false);
                relationAddModeButton->setActive(false);
                usingModesManager->setUsingMode(UsingModesManager::UsingModeType::normal);
            } else if(polygonEditModeButton->isTouched(window) && !polygonEditModeButton->isActive()) {
                normalModeButton->setActive(false);
                polygonEditModeButton->setActive(true);
                relationAddModeButton->setActive(false);
                usingModesManager->setUsingMode(UsingModesManager::UsingModeType::edit);
            } else if(relationAddModeButton->isTouched(window) && !relationAddModeButton->isActive()) {
                normalModeButton->setActive(false);
                polygonEditModeButton->setActive(false);
                relationAddModeButton->setActive(true);
                usingModesManager->setUsingMode(UsingModesManager::UsingModeType::relation);
            }
        }
        isMouseLeftButtonPressed = true;
    } else {
        isMouseLeftButtonPressed = false;
    }
}

void UpperPanel::draw(RenderTarget &target, RenderStates states) const {
    target.draw(rectangle, states);
    target.draw(*normalModeButton, states);
    target.draw(*polygonEditModeButton, states);
    target.draw(*relationAddModeButton, states);
}
