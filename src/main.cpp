#include <iostream>
#include "view.hpp"
#include "controller.hpp"
#include "model.hpp"

int main()
{   
    ShapeManager shapeManager;
    shapeManager.seedData();

    View menu;

    Controller controller(shapeManager, menu);
    controller.run();

    return 0;
}
