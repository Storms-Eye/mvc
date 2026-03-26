#include <iostream>
#include "view.hpp"
#include "controller.hpp"
#include "model.hpp"

int main()
{   
    ShapeManager shapeManager;
    shapeManager.seedData();

    Menu menu;

    Controller controller(shapeManager, menu);
    controller.run();

    return 0;
}
