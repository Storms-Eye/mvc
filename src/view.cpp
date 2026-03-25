#include <iostream>

class Menu
{
private:
    std::string lastMessage;
    
public:
    void clearScreen()
    {
        for (int i = 0; i < 30; ++i)
        {
            std::cout << '\n';
        }
    }
    void drawHeader()
    {
        std::cout << "==============================================\n";
        std::cout << "            SHAPE MANAGER MONOLITH            \n";
        std::cout << "==============================================\n";
        std::cout << "Last message: " << lastMessage << "\n\n";
    }
    void drawShapes()
    {
        if (shapes.empty())
        {
            std::cout << "No shapes in the scene.\n\n";
            return;
        }

        std::cout << left
                  << setw(5) << "ID"
                  << setw(11) << "Type"
                  << setw(10) << "X"
                  << setw(10) << "Y"
                  << setw(10) << "Width"
                  << setw(10) << "Height"
                  << setw(18) << "Color"
                  << setw(10) << "Selected"
                  << "\n";

        std::cout << string(85, '-') << "\n";
        for (const auto &s : shapes)
        {
            ostringstream colorText;
            colorText << "(" << s.color.r << "," << s.color.g << "," << s.color.b << ")";

            std::cout << left
                      << setw(5) << s.id
                      << setw(12) << s.type
                      << setw(10) << s.x
                      << setw(10) << s.y
                      << setw(10) << s.width
                      << setw(10) << s.height
                      << setw(18) << colorText.str()
                      << setw(10) << (s.selected ? "Yes" : "No")
                      << "\n";
        }

        std::cout << "\n";
    }
    void drawMenu()
    {
        std::cout << "Menu:\n";
        std::cout << " 1. Add Rectangle\n";
        std::cout << " 2. Add Circle\n";
        std::cout << " 3. Select Shape By ID\n";
        std::cout << " 4. Move Selected Shape\n";
        std::cout << " 5. Resize Selected Shape\n";
        std::cout << " 6. Change Selected Shape Color\n";
        std::cout << " 7. Delete Selected Shape\n";
        std::cout << " 8. Show Shape Statistics\n";
        std::cout << " 9. Save Shapes To File\n";
        std::cout << "10. Load Shapes From File\n";
        std::cout << "11. Sort Shapes By Area\n";
        std::cout << "12. Search Shapes By Type\n";
        std::cout << "13. Clear All Shapes\n";
        std::cout << "14. Exit\n\n";
    }
}
