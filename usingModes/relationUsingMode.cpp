#include "relationUsingMode.h"

using namespace sf;
using namespace std;

RelationUsingMode::RelationUsingMode(
    Window* window,
    Canvas* canvas,
    EdgeTouchDetector* edgeTouchDetector,
    PolygonsContainer* polygonsContainer
) {
    this->window = window;
    this->canvas = canvas;
    this->edgeTouchDetector = edgeTouchDetector;
    this->polygonsContainer = polygonsContainer;
}

RelationUsingMode::~RelationUsingMode() {
    if(textBox != nullptr)
        delete textBox;

    if(touchedEdgeData != nullptr)
        delete touchedEdgeData;
}

void RelationUsingMode::update() {
    auto mousePositionOnCanvas = getMousePositionOnCanvas();
    if(!isMouseOnCanvas(mousePositionOnCanvas))
        return;

    if(textBox != nullptr)
        textBox->update();

    if(textBox == nullptr) {
        polygonsContainer->clearHighlight();
        touchedEdgeData = nullptr;
        auto currentTouchedEdgeData = edgeTouchDetector->getTouchedEdge(mousePositionOnCanvas);
        if(currentTouchedEdgeData != nullptr) {
            polygonsContainer->setHighlighten(currentTouchedEdgeData);
            touchedEdgeData = currentTouchedEdgeData;
        } else {
            return;
        }
    }

    if(!isMouseLeftButtonPressed && Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = true;
        if(touchedEdgeData != nullptr && textBox == nullptr) {
            auto len = polygonsContainer->getPolygons()[touchedEdgeData->polygonIndex].getEdgeLength(touchedEdgeData->startPointIndex);
            auto points = polygonsContainer->getPolygons()[touchedEdgeData->polygonIndex].getPoints();
            auto position = (points[touchedEdgeData->startPointIndex] + points[touchedEdgeData->finishPointIndex]) / 2;
            textBox = new TextBox(len, Vector2f(position), 20);
        }
    } else if(!Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = false;
    }

    if(!isEnterKeyPressed && Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
        isEnterKeyPressed = true;
        if(textBox != nullptr) {
            auto len = textBox->getValue();
            polygonsContainer->setEdgeLength(touchedEdgeData, len);
            delete textBox;
            delete touchedEdgeData;
            textBox = nullptr;
            touchedEdgeData = nullptr;
        }
    } else if(!Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
        isEnterKeyPressed = false;
    }
}

void RelationUsingMode::draw() {
    if(textBox != nullptr)
        textBox->draw(canvas);
}

Vector2i RelationUsingMode::getMousePositionOnCanvas() {
    auto canvasPosition = canvas->getPosition();
    auto mousePosition = Mouse::getPosition(*window);
    return Vector2i(mousePosition.x - canvasPosition.x, mousePosition.y - canvasPosition.y);
}

bool RelationUsingMode::isMouseOnCanvas(Vector2i mousePositionOnCanvas) {
    return mousePositionOnCanvas.x >= 0 &&
        mousePositionOnCanvas.y >= 0 &&
        mousePositionOnCanvas.x < canvas->getSize().x &&
        mousePositionOnCanvas.y < canvas->getSize().y;
}
