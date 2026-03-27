#include <iostream>
#include <string>
#include <vector>
#include "model.hpp"

class View
{
private:
    std::string lastMessage;

public:
    void pause();

    void readShape(Shape &shape);

    int readInt(const std::string &prompt);
    double readDouble(const std::string &prompt);

    std::string readString(const std::string &prompt);
    void clearScreen();
    void drawHeader();
    void drawShapes(const std::vector<Shape>& shapes);
    void drawMenu();
    void showStatistics(const std::vector<Shape>& shapes);
};
