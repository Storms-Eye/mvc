#include <string>
#include <iostream>
#include <vector>
#include <istream>
#include <ostream>

struct Color
{
    int r = 255;
    int g = 255;
    int b = 255;
};

class Shape
{
public:
    Shape(const std::string &type);

    void moveSelectedShape();

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
    void addShape(const Shape &s);


    void saveToFile();
    void loadFromFile();

    void resizeSelectedShape();
    void recolorSelectedShape();
    void deleteSelectedShape();

    void seedData();

    Shape *getSelectedShape();
    const Shape *getSelectedShape() const;
    double computeArea(const Shape &s) const;

    void selectShape();
    void searchByType();
    void clearAllShapes();

    void sortShapesByArea();
};
