#include "model.hpp"
#include <sstream>

Shape::Shape(const std::string &type)
{
    double x = readDouble("Enter x position: ");
    double y = readDouble("Enter y position: ");
    double w = readDouble("Enter width: ");
    double h = readDouble("Enter height: ");

    if (w <= 0 || h <= 0)
    {
        lastMessage = "Width and height must be positive";
        pause();
        return;
    }

    int r = readInt("Enter color R (0-255): ");
    int g = readInt("Enter color G (0-255): ");
    int b = readInt("Enter color B (0-255): ");

    r = clampColor(r);
    g = clampColor(g);
    b = clampColor(b);

    for (auto &s : shapes)
    {
        s.selected = false;
    }

    id = nextId++;
    type = type;
    x = x;
    y = y;
    width = w;
    height = h;
    color = {r, g, b};
    selected = true;

    if (type == "Circle")
    {
        height = width;
    }

    lastMessage = type + " added and selected";
    pause();
}

void ShapeManager::addShape(const Shape &s)
{
    shapes.push_back(s);
}

void Shape::moveSelectedShape()
{
    Shape *s = getSelectedShape();
    if (!s)
    {
        lastMessage = "No selected shape to move";
        pause();
        return;
    }

    double dx = readDouble("Enter delta x: ");
    double dy = readDouble("Enter delta y: ");

    s->x += dx;
    s->y += dy;

    ostd::stringstream msg;
    msg << "Moved shape " << s->id << " to (" << s->x << ", " << s->y << ")";
    lastMessage = msg.str();
    pause();
}
void ShapeManager::resizeSelectedShape()
{
    Shape *s = getSelectedShape();
    if (!s)
    {
        lastMessage = "No selected shape to resize";
        pause();
        return;
    }

    double newW = readDouble("Enter new width: ");
    double newH = readDouble("Enter new height: ");

    if (newW <= 0 || newH <= 0)
    {
        lastMessage = "Width and height must be positive";
        pause();
        return;
    }

    s->width = newW;
    s->height = (s->type == "Circle") ? newW : newH;

    lastMessage = "Selected shape resized";
    pause();
}

void ShapeManager::recolorSelectedShape()
{
    Shape *s = getSelectedShape();
    if (!s)
    {
        lastMessage = "No selected shape to recolor";
        pause();
        return;
    }

    int r = readInt("Enter new R (0-255): ");
    int g = readInt("Enter new G (0-255): ");
    int b = readInt("Enter new B (0-255): ");

    s->color.r = clampColor(r);
    s->color.g = clampColor(g);
    s->color.b = clampColor(b);

    lastMessage = "Selected shape color updated";
    pause();
}
void ShapeManager::deleteSelectedShape()
{
    auto it = remove_if(shapes.begin(), shapes.end(), [](const Shape &s)
    {
        return s.selected;
    });

    if (it == shapes.end())
    {
        lastMessage = "No selected shape to delete";
        pause();
        return;
    }

    shapes.erase(it, shapes.end());

    if (!shapes.empty())
    {
        shapes.front().selected = true;
    }

    lastMessage = "Selected shape deleted";
    pause();
}

void ShapeManager::seedData()
{
    shapes.push_back({nextId++, "Rectangle", 10, 10, 40, 20, {255, 0, 0}, true});
    shapes.push_back({nextId++, "Circle", 30, 15, 25, 25, {0, 255, 0}, false});
    shapes.push_back({nextId++, "Rectangle", 5, 40, 15, 10, {0, 0, 255}, false});
}

Shape *ShapeManager::getSelectedShape()
{
    for (auto &s : shapes)
    {
        if (s.selected)
        {
            return &s;
        }
    }
    return nullptr;
}

const Shape *ShapeManager::getSelectedShape() const
{
    for (const auto &s : shapes)
    {
        if (s.selected)
        {
            return &s;
        }
    }
    return nullptr;
}

double ShapeManager::computeArea(const Shape &s) const
{
    if (s.type == "Rectangle")
    {
        return s.width * s.height;
    }
    if (s.type == "Circle")
    {
        double radius = s.width / 2.0;
        return 3.14159265358979323846 * radius * radius;
    }
    return 0.0;
}

void ShapeManager::selectShape()
{
    if (shapes.empty())
    {
        lastMessage = "No shapes available to select";
        pause();
        return;
    }

    int id = readInt("Enter shape ID to select: ");
    bool found = false;

    for (auto &s : shapes)
    {
        s.selected = false;
        if (s.id == id)
        {
            s.selected = true;
            found = true;
        }
    }

    lastMessage = found ? "Shape selected" : "Shape ID not found";
    pause();
}

void ShapeManager::searchByType()
{
    clearScreen();
    drawHeader();

    string query = readString("Enter type to search for: ");
    for (char &c : query)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    std::cout << "\nSearch Results\n";
    std::cout << "--------------\n";

    int matches = 0;
    for (const auto &s : shapes)
    {
        std::string typeLower = s.type;
        for (char &c : typeLower)
        {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }

        if (typeLower.find(query) != string::npos)
        {
            std::cout << "ID " << s.id << ": " << s.type
                 << " at (" << s.x << ", " << s.y << ")\n";
            matches++;
        }
    }

    if (matches == 0)
    {
        std::cout << "No shapes matched the search.\n";
    }

    pause();
    lastMessage = "Search complete";
}

void ShapeManager::clearAllShapes()
{
    std::string confirm = readString("Type YES to clear all shapes: ");
    if (confirm == "YES")
    {
        shapes.clear();
        lastMessage = "All shapes cleared";
    }
    else
    {
        lastMessage = "Clear operation canceled";
    }
    pause();
}
}

void ShapeManager::sortShapesByArea()
{
    sort(shapes.begin(), shapes.end(), [this](const Shape &a, const Shape &b)
    {
        return computeArea(a) < computeArea(b);
    });

    lastMessage = "Shapes sorted by area";
    pause();
}