#include "model.hpp"
#include "view.hpp"
#include <iostream>
#include <string>
#include <vector>

class Controller
{
private:
    ShapeManager& manager;
    Menu& menu;
    bool running = true;
    std::string lastMessage;

public:
    Controller(ShapeManager& model, Menu& menu) : manager(model), menu(menu) {}

    void handleMenuChoice();
    void run();
};
