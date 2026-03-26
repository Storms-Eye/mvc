#include "view.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int clampColor(int value)
{
    if (value < 0)
        return 0;
    if (value > 255)
        return 255;
    return value;
}

void Menu::clearScreen()
{
    for (int i = 0; i < 30; ++i)
    {
        std::cout << '\n';
    }
}

void Menu::readShape(Shape &shape)
{
    int r, g, b;
    double x, y, w, h;

    x = readDouble("Enter x position: ");
    y = readDouble("Enter y position: ");
    w = readDouble("Enter width: ");
    h = readDouble("Enter height: ");

    if (w <= 0 || h <= 0)
    {
        lastMessage = "Width and height must be positive";
        pause();
        return;
    }

    r = readInt("Enter color R (0-255): ");
    g = readInt("Enter color G (0-255): ");
    b = readInt("Enter color B (0-255): ");

    r = clampColor(r);
    g = clampColor(g);
    b = clampColor(b);

    shape.color = {r, g, b};
    shape.x = x;
    shape.y = y;
    shape.width = w;
    shape.height = h;
}

void Menu::drawHeader()
{
    std::cout << "==============================================\n";
    std::cout << "            SHAPE MANAGER MONOLITH            \n";
    std::cout << "==============================================\n";
    std::cout << "Last message: " << lastMessage << "\n\n";
}

void Menu::drawShapes(const std::vector<Shape> &shapes)
{
    if (shapes.empty())
    {
        std::cout << "No shapes in the scene.\n\n";
        return;
    }

    std::cout << std::left
              << std::setw(5) << "ID"
              << std::setw(11) << "Type"
              << std::setw(10) << "X"
              << std::setw(10) << "Y"
              << std::setw(10) << "Width"
              << std::setw(10) << "Height"
              << std::setw(18) << "Color"
              << std::setw(10) << "Selected"
              << "\n";

    std::cout << std::string(85, '-') << "\n";
    for (const auto &s : shapes)
    {
        std::ostringstream colorText;
        colorText << "(" << s.color.r << "," << s.color.g << "," << s.color.b << ")";

        std::cout << std::left
                  << std::setw(5) << s.id
                  << std::setw(12) << s.type
                  << std::setw(10) << s.x
                  << std::setw(10) << s.y
                  << std::setw(10) << s.width
                  << std::setw(10) << s.height
                  << std::setw(18) << colorText.str()
                  << std::setw(10) << (s.selected ? "Yes" : "No")
                  << "\n";
    }

    std::cout << "\n";
}

void Menu::drawMenu()
{
    std::cout << "Menu:\n";
    std::cout << " 1. Add Rectangle\n";
    std::cout << " 2. Add Circle\n";
    std::cout << " 3. Select Shape By ID\n";
    std::cout << " 4. Move Selected Shape\n";
    std::cout << " 5. Resize Selected Shape\n";
    std::cout << " 6. Change Selected Shape Color\n";
    std::cout << " 7. Delete Selected Shape\n";
    std::cout << " 8. Show Shape Statistics\n";
    std::cout << " 9. Save Shapes To File\n";
    std::cout << "10. Load Shapes From File\n";
    std::cout << "11. Sort Shapes By Area\n";
    std::cout << "12. Search Shapes By Type\n";
    std::cout << "13. Clear All Shapes\n";
    std::cout << "14. Exit\n\n";
}

void Menu::showStatistics(const std::vector<Shape> &shapes)
{
    drawHeader();

    int rectangles = 0;
    int circles = 0;
    double totalArea = 0.0;

    for (const auto &s : shapes)
    {
        if (s.type == "Rectangle")
        {
            rectangles++;
        }
        else if (s.type == "Circle")
        {
            circles++;
        }
        totalArea += computeArea(s);
    }

    std::cout << "Scene Statistics\n";
    std::cout << "----------------\n";
    std::cout << "Total shapes: " << shapes.size() << "\n";
    std::cout << "Rectangles : " << rectangles << "\n";
    std::cout << "Circles    : " << circles << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total area : " << totalArea << "\n";

    const Shape *selected = getSelectedShape();
    if (selected)
    {
        std::cout << "Selected ID: " << selected->id << "\n";
        std::cout << "Selected area: " << computeArea(*selected) << "\n";
    }
    else
    {
        std::cout << "Selected ID: none\n";
    }

    pause();
    lastMessage = "Displayed statistics";
}

std::string Menu::readString(const std::string &prompt)
{
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int Menu::readInt(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);

        std::stringstream ss(line);
        int value;
        char extra;

        if (ss >> value && !(ss >> extra))
        {
            return value;
        }

        std::cout << "Invalid integer input. Try again.\n";
    }
}

double Menu::readDouble(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);

        std::stringstream ss(line);
        double value;
        char extra;

        if (ss >> value && !(ss >> extra))
        {
            return value;
        }

        std::cout << "Invalid numeric input. Try again.\n";
    }
}

void Menu::pause()
{
    std::cout << "\nPress Enter to continue...";
    std::string dummy;
    std::getline(std::cin, dummy);
}