 void clearScreen() {
        for (int i = 0; i < 30; ++i) {
            cout << '\n';
        }
    }
void drawHeader() {
        cout << "==============================================\n";
        cout << "            SHAPE MANAGER MONOLITH            \n";
        cout << "==============================================\n";
        cout << "Last message: " << lastMessage << "\n\n";
    }
void drawShapes() {
        if (shapes.empty()) {
            cout << "No shapes in the scene.\n\n";
            return;
        }

        cout << left
             << setw(5) << "ID"
             << setw(11) << "Type"
             << setw(10) << "X"
             << setw(10) << "Y"
             << setw(10) << "Width"
             << setw(10) << "Height"
             << setw(18) << "Color"
             << setw(10) << "Selected"
             << "\n";

        cout << string(85, '-') << "\n";
for (const auto& s : shapes) {
            ostringstream colorText;
            colorText << "(" << s.color.r << "," << s.color.g << "," << s.color.b << ")";

            cout << left
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

        cout << "\n";
    }
void drawMenu() {
        cout << "Menu:\n";
        cout << " 1. Add Rectangle\n";
        cout << " 2. Add Circle\n";
        cout << " 3. Select Shape By ID\n";
        cout << " 4. Move Selected Shape\n";
        cout << " 5. Resize Selected Shape\n";
        cout << " 6. Change Selected Shape Color\n";
        cout << " 7. Delete Selected Shape\n";
        cout << " 8. Show Shape Statistics\n";
        cout << " 9. Save Shapes To File\n";
        cout << "10. Load Shapes From File\n";
        cout << "11. Sort Shapes By Area\n";
        cout << "12. Search Shapes By Type\n";
        cout << "13. Clear All Shapes\n";
        cout << "14. Exit\n\n";
    }

