#include "controller.hpp"

void ShapeManager::handleMenuChoice()
{
    int choice = readInt("Enter choice: ");

    switch (choice)
    {
    case 1:
        addShape("Rectangle");
        break;
    case 2:
        addShape("Circle");
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
        showStatistics();
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

int ShapeManager::readInt(const string &prompt)
{
    while (true)
    {
        cout << prompt;
        string line;
        getline(cin, line);

        stringstream ss(line);
        int value;
        char extra;

        if (ss >> value && !(ss >> extra))
        {
            return value;
        }

        cout << "Invalid integer input. Try again.\n";
    }
}