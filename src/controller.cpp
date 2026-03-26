#include "controller.hpp"

void Controller::run()
{
    bool res = true;
    while (res)
    {
        menu.clearScreen();
        menu.drawHeader();
        menu.drawShapes(manager.getShapes());
        menu.drawMenu();
        
        manager.handleMenuChoice();
    }
}


void Controller::handleMenuChoice()
{
    int choice = readInt("Enter choice: ");

    switch (choice)
    {
    case 1:
        manager.addShape(Shape("Rectangle"));
        break;
    case 2:
        manager.addShape(Shape("Circle"));
        break;
    case 3:
        selectShape();
        break;
    case 4:
        moveSelectedShape();
        break;
    case 5:
        resizeSelectedShape();
        break;
    case 6:
        recolorSelectedShape();
        break;
    case 7:
        deleteSelectedShape();
        break;
    case 8:
        showStatistics(getShapes());
        break;
    case 9:
        saveToFile();
        break;
    case 10:
        loadFromFile();
        break;
    case 11:
        sortShapesByArea();
        break;
    case 12:
        searchByType();
        break;
    case 13:
        clearAllShapes();
        break;
    case 14:
        running = false;
        lastMessage = "Exiting program";
        break;
    default:
        lastMessage = "Invalid menu choice";
        pause();
        break;
    }
}

const std::vector<Shape> &ShapeManager::getShapes()
{
    return shapes;
}
