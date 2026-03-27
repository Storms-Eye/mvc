#pragma once

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

struct Color
{
    int r = 255;
    int g = 255;
    int b = 255;
};

struct Shape
{
    int id = 0;
    std::string type;
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    Color color;
    bool selected = false;
};

class ShapeManager
{
private:
    std::vector<Shape> shapes;
    int nextId = 1;
    bool running = true;

public:
    const std::vector<Shape> &getShapes();
    void addShape(const std::string &type, Shape &s);

    bool saveToFile(const std::string &filename);
    bool loadFromFile(const std::string &filename);

    bool resizeSelectedShape(int newW, int newH);
    bool recolorSelectedShape(int r, int g, int b);
    bool deleteSelectedShape();
    bool moveSelectedShape(int dx, int dy, std::string &message);

    void seedData();

    Shape *getSelectedShape();
    const Shape *getSelectedShape() const;
    double computeArea(const Shape &s) const;

    bool selectShape(int id);
    void searchByType(std::string &query);
    void clearAllShapes();

    void sortShapesByArea();
};
