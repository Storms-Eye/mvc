#include <string>

struct Color {
    int r = 255;
    int g = 255;
    int b = 255;
};

struct Shape {
    int id = 0;
    std::string type;
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    Color color;
    bool selected = false;
};

class Model
{
public:
    void seedData();
    void addShape(const std::string &type);
    void moveSelectedShape();
    void resizeSelectedShape();
    void recolorSelectedShape();
    void deleteSelectedShape();
    void sortShapesByArea();
};
