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

        handleMenuChoice();
    }
}

void Controller::handleMenuChoice()
{
    int choice = menu.readInt("Enter choice: ");

    Shape s;
    std::string input();
    bool res = false;

    switch (choice)
    {
    case 1:
        menu.readShape(s);
        manager.addShape("Rectangle", s);

        lastMessage = s.type + " added and selected";
        menu.pause();
        break;
    case 2:
        menu.readShape(s);
        manager.addShape("Circle", s);

        lastMessage = s.type + " added and selected";
        menu.pause();
        break;
    case 3:
        if (manager.getShapes().empty())
        {
            lastMessage = "No shapes available to select";
            menu.pause();
            break;
        }

        int id = menu.readInt("Enter shape ID to select: ");
        res = manager.selectShape(id);
        if (!res)
        {
            lastMessage = "Shape ID not found";
        }
        else
        {
            lastMessage = "Shape selected";
        }

        menu.pause();
        break;
    case 4:
        double dx = menu.readDouble("Enter delta x: ");
        double dy = menu.readDouble("Enter delta y: ");
        res = manager.moveSelectedShape(dx, dy, input);
        if (res)
        {
            lastMessage = input;
        }
        else
        {
            lastMessage = "No selected shape to move";
        }
        break;
    case 5:
        double newW = menu.readDouble("Enter new width: ");
        double newH = menu.readDouble("Enter new height: ");

        if (newW <= 0 || newH <= 0)
        {
            lastMessage = "Width and height must be positive";
            menu.pause();
            return;
        }
        res = manager.resizeSelectedShape(newW, newH);
        if (res)
        {
            lastMessage = "Selected shape resized";
        }
        else
        {
            lastMessage = "No selected shape to resize";
        }
        menu.pause();
        break;
    case 6:
        int r = menu.readInt("Enter new R (0-255): ");
        int g = menu.readInt("Enter new G (0-255): ");
        int b = menu.readInt("Enter new B (0-255): ");

        res = manager.recolorSelectedShape(r, g, b);
        if (res)
        {
            lastMessage = "Selected shape color updated";
        }
        else
        {
            lastMessage = "No selected shape to recolor";
        }
        menu.pause();
        break;
    case 7:

        res = manager.deleteSelectedShape();
        if (res)
        {
            lastMessage = "Selected shape deleted";
        }
        else
        {
            lastMessage = "No selected shape to delete";
        }
        menu.pause();
        break;
    case 8:
        menu.showStatistics(manager.getShapes());
        break;
    case 9:
        input = menu.readString("Enter filename to save: ");
        res = manager.saveToFile(input);

        if (res)
        {
            lastMessage = "Shapes saved to file";
        }
        else
        {
            lastMessage = "Failed to save shapes to file";
        }
        menu.pause();
        break;
    case 10:
        input = menu.readString("Enter filename to load: ");
        res = manager.loadFromFile(input);

        if (res)
        {
            lastMessage = "Shapes loaded from file";
        }
        else
        {
            lastMessage = "Failed to load file";
        }
        menu.pause();
        break;
    case 11:
        manager.sortShapesByArea();
        lastMessage = "Shapes sorted by area";
        menu.pause();
        break;
    case 12:
        menu.clearScreen();
        menu.drawHeader();
        input = menu.readString("Enter type to search for: ");
        manager.searchByType(input);

        lastMessage = "Search complete";
        menu.pause();

        break;
    case 13:
        input = menu.readString("Type YES to clear all shapes: ");
        if (input == "YES")
        {
            manager.clearAllShapes();
            lastMessage = "All shapes cleared";
        }
        else
        {
            lastMessage = "Clear operation canceled";
        }
        menu.pause();
        break;
    case 14:
        running = false;
        lastMessage = "Exiting program";
        break;
    default:
        lastMessage = "Invalid menu choice";
        menu.pause();
        break;
    }
}

const std::vector<Shape> &ShapeManager::getShapes()
{
    return shapes;
}
