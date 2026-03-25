#include "model.hpp"

void Model::seedData()
{
    shapes.push_back({nextId++, "Rectangle", 10, 10, 40, 20, {255, 0, 0}, true});
    shapes.push_back({nextId++, "Circle", 30, 15, 25, 25, {0, 255, 0}, false});
    shapes.push_back({nextId++, "Rectangle", 5, 40, 15, 10, {0, 0, 255}, false});
}

void Model::addShape(const string &type)
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

    Shape s;
    s.id = nextId++;
    s.type = type;
    s.x = x;
    s.y = y;
    s.width = w;
    s.height = h;
    s.color = {r, g, b};
    s.selected = true;

    if (type == "Circle")
    {
        s.height = s.width;
    }

    shapes.push_back(s);
    lastMessage = type + " added and selected";
    pause();
}

void Model::moveSelectedShape()
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

    ostringstream msg;
    msg << "Moved shape " << s->id << " to (" << s->x << ", " << s->y << ")";
    lastMessage = msg.str();
    pause();
}
void Model::resizeSelectedShape()
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

void Model::recolorSelectedShape()
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
void Model::deleteSelectedShape()
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

void Model::sortShapesByArea()
{
    sort(shapes.begin(), shapes.end(), [this](const Shape &a, const Shape &b)
    {
        return computeArea(a) < computeArea(b);
    });

    lastMessage = "Shapes sorted by area";
    pause();
}