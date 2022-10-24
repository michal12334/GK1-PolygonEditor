#include <SFML/Graphics.hpp>
#include "globalModules.h"
#include "buttons/button.h"
#include "panels/upperPanel.h"
#include "canvases/canvas.h"
#include "usingModes/editUsingMode.h"

using namespace sf;
using namespace std;

void createScene(PolygonsContainer* polygonsContainer, PointDrawer* pointDrawer, LineDrawer* lineDrawer) {
    vector<Vector2i> points;
    points.push_back(Vector2i(100, 100));
    points.push_back(Vector2i(300, 150));
    points.push_back(Vector2i(130, 170));
    points.push_back(Vector2i(180, 220));
    points.push_back(Vector2i(90, 220));
    Polygon p1(points, pointDrawer, lineDrawer);
    polygonsContainer->addPolygon(p1);
    auto e = new TouchedEdgeData(0, 0, 1, p1);
    polygonsContainer->setEdgeLength(e);
    e->startPointIndex = 3;
    e->finishPointIndex = 4;
    polygonsContainer->setEdgeLength(e);

    points.clear();
    points.push_back(Vector2i(400, 300));
    points.push_back(Vector2i(500, 350));
    points.push_back(Vector2i(550, 400));
    points.push_back(Vector2i(600, 500));
    points.push_back(Vector2i(550, 600));
    points.push_back(Vector2i(500, 650));
    points.push_back(Vector2i(400, 700));
    points.push_back(Vector2i(300, 650));
    points.push_back(Vector2i(250, 600));
    points.push_back(Vector2i(200, 500));
    points.push_back(Vector2i(250, 400));
    points.push_back(Vector2i(300, 350));
    Polygon p2(points, pointDrawer, lineDrawer);
    polygonsContainer->addPolygon(p2);
    e->polygonIndex = 1;
    e->polygon = p2;
    e->startPointIndex = 0;
    e->finishPointIndex = 1;
    polygonsContainer->setEdgeLength(e);
    e->startPointIndex = 1;
    e->finishPointIndex = 2;
    polygonsContainer->setEdgeLength(e);
    e->startPointIndex = 2;
    e->finishPointIndex = 3;
    polygonsContainer->setEdgeLength(e);
    e->startPointIndex = 3;
    e->finishPointIndex = 4;
    polygonsContainer->setEdgeLength(e);
    e->startPointIndex = 4;
    e->finishPointIndex = 5;
    polygonsContainer->setEdgeLength(e);
    e->startPointIndex = 5;
    e->finishPointIndex = 6;
    polygonsContainer->setEdgeLength(e);
    e->startPointIndex = 8;
    e->finishPointIndex = 9;
    polygonsContainer->setEdgeLength(e);
    e->startPointIndex = 9;
    e->finishPointIndex = 10;
    polygonsContainer->setEdgeLength(e);

    delete e;
}

int main() {
    GlobalModules globalModules;
    auto window = globalModules.getWindow();
    auto upperPanel = globalModules.getUpperPanel();
    auto canvas = globalModules.getCanvas();
    auto polygons = globalModules.getPolygonsContainer();
    auto usingModesManager = globalModules.getUsingModesManager();

    createScene(globalModules.getPolygonsContainer(), globalModules.getPointDrawer(), globalModules.getLineDrawer());

    sf::Event event;
    while (window->isOpen()) {
        usingModesManager->updateCurrentUsingMode();
        upperPanel->update();

        window->clear();
        window->draw(*upperPanel);
        canvas->clear();
        polygons->draw();
        usingModesManager->drawCurrentUsingMode();
        canvas->updateTexture();
        window->draw(*canvas);
        window->display();

        while(window->pollEvent(event))
            if (event.type == Event::Closed)
                window->close();
    }

    return 0;
}
