#pragma once

#include "model.hpp"
#include "view.hpp"
#include <iostream>
#include <string>
#include <vector>

class Controller
{
private:
    ShapeManager& manager;
    View& menu;
    bool running = true;
    std::string lastMessage;

public:
    Controller(ShapeManager& model, View& menu) : manager(model), menu(menu) {}

    void handleMenuChoice();
    void run();
};
