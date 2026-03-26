#include "model.hpp"
#include "view.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int clampColor(int value)
{
    if (value < 0)
        return 0;
    if (value > 255)
        return 255;
    return value;
}

void ShapeManager::addShape(const std::string &type, Shape &s)
{
    for (auto &s : shapes)
    {
        s.selected = false;
    }

    s.selected = true;
    s.id = nextId++;
    s.type = type;

    shapes.push_back(s);
}

bool ShapeManager::moveSelectedShape(int dx, int dy, std::string &message)
{
    Shape *s = getSelectedShape();
    if (!s)
    {
        return false;
    }

    s->x += dx;
    s->y += dy;

    std::stringstream msg;
    msg << "Moved shape " << s->id << " to (" << s->x << ", " << s->y << ")";
    message = msg.str();
    
    return true;
}

bool ShapeManager::resizeSelectedShape(int newW, int newH)
{
    Shape *s = getSelectedShape();
    if (!s)
    {
        return false;
    }

    s->width = newW;
    s->height = (s->type == "Circle") ? newW : newH;

    return true;
}

bool ShapeManager::recolorSelectedShape(int r, int g, int b)
{
    Shape *s = getSelectedShape();
    if (!s)
    {
        return false;
    }

    s->color.r = clampColor(r);
    s->color.g = clampColor(g);
    s->color.b = clampColor(b);

    return true;
}

bool ShapeManager::deleteSelectedShape()
{
    auto it = remove_if(shapes.begin(), shapes.end(), [](const Shape &s)
    {
        return s.selected;
    });

    if (it == shapes.end())
    {
        return false;
    }

    shapes.erase(it, shapes.end());

    if (!shapes.empty())
    {
        shapes.front().selected = true;
    }
    return true;
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

bool ShapeManager::selectShape(int id)
{
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

    return found;
}

void ShapeManager::searchByType(std::string &query)
{
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

        if (typeLower.find(query) != std::string::npos)
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
}

void ShapeManager::clearAllShapes()
{
    shapes.clear();
    // Old code didn't reset ID.
    nextId = 1;
}

void ShapeManager::sortShapesByArea()
{
    sort(shapes.begin(), shapes.end(), [this](const Shape &a, const Shape &b)
    {
        return computeArea(a) < computeArea(b);
    });
}

bool ShapeManager::saveToFile(const std::string &filename)
{
    std::ofstream out(filename);

    if (!out)
    {
        return false;
    }

    out << nextId << "\n";
    out << shapes.size() << "\n";

    for (const auto &s : shapes)
    {
        out << s.id << "|"
            << s.type << "|"
            << s.x << "|"
            << s.y << "|"
            << s.width << "|"
            << s.height << "|"
            << s.color.r << "|"
            << s.color.g << "|"
            << s.color.b << "|"
            << s.selected << "\n";
    }

    return true;
}

bool ShapeManager::loadFromFile(const std::string &filename)
{
    std::ifstream in(filename);

    if (!in)
    {
        return false;
    }

    std::vector<Shape> loadedShapes;
    int loadedNextId = 1;
    size_t count = 0;

    std::string line;
    if (!getline(in, line))
    {
        return false;
    }
    loadedNextId = stoi(line);

    if (!getline(in, line))
    {
        return false;
    }
    count = static_cast<size_t>(stoul(line));

    for (size_t i = 0; i < count; ++i)
    {
        if (!getline(in, line))
        {
            return false;
        }

        std::stringstream ss(line);
        std::vector<std::string> parts;
        std::string part;

        while (getline(ss, part, '|'))
        {
            parts.push_back(part);
        }

        if (parts.size() != 10)
        {
            return false;
        }

        Shape s;
        s.id = stoi(parts[0]);
        s.type = parts[1];
        s.x = stod(parts[2]);
        s.y = stod(parts[3]);
        s.width = stod(parts[4]);
        s.height = stod(parts[5]);
        s.color.r = stoi(parts[6]);
        s.color.g = stoi(parts[7]);
        s.color.b = stoi(parts[8]);
        s.selected = (parts[9] == "1");

        loadedShapes.push_back(s);
    }

    shapes = loadedShapes;
    nextId = loadedNextId;
}