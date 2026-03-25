//view.cpp


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

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
		void showStatistics() {
        clearScreen();
        drawHeader();

        int rectangles = 0;
        int circles = 0;
        double totalArea = 0.0;

        for (const auto& s : shapes) {
            if (s.type == "Rectangle") {
                rectangles++;
            } else if (s.type == "Circle") {
                circles++;
            }
            totalArea += computeArea(s);
        }

        cout << "Scene Statistics\n";
        cout << "----------------\n";
        cout << "Total shapes: " << shapes.size() << "\n";
        cout << "Rectangles : " << rectangles << "\n";
        cout << "Circles    : " << circles << "\n";
        cout << fixed << setprecision(2);
        cout << "Total area : " << totalArea << "\n";

        const Shape* selected = getSelectedShape();
        if (selected) {
            cout << "Selected ID: " << selected->id << "\n";
            cout << "Selected area: " << computeArea(*selected) << "\n";
        } else {
            cout << "Selected ID: none\n";
        }

        pause();
        lastMessage = "Displayed statistics";
    }
void saveToFile() {
        string filename = readString("Enter filename to save: ");
        ofstream out(filename);

        if (!out) {
            lastMessage = "Failed to open file for saving";
            pause();
            return;
        }

        out << nextId << "\n";
        out << shapes.size() << "\n";

        for (const auto& s : shapes) {
            out << s.id << "|"
                << s.type << "|"
                << s.x << "|"
                << s.y << "|"
                << s.width << "|"
                << s.height << "|"
                << s.color.r << "|"
                << s.color.g << "|"
                << s.color.b << "|"
                << s.selected << "\n";
        }

        lastMessage = "Shapes saved to file";
        pause();
    }
void loadFromFile() {
        string filename = readString("Enter filename to load: ");
        ifstream in(filename);

        if (!in) {
            lastMessage = "Failed to open file for loading";
            pause();
            return;
        }

        vector<Shape> loadedShapes;
        int loadedNextId = 1;
        size_t count = 0;

        string line;
        if (!getline(in, line)) {
            lastMessage = "Invalid file format";
            pause();
            return;
        }
        loadedNextId = stoi(line);

        if (!getline(in, line)) {
            lastMessage = "Invalid file format";
            pause();
            return;
        }
        count = static_cast<size_t>(stoul(line));
				for (size_t i = 0; i < count; ++i) {
            if (!getline(in, line)) {
                lastMessage = "Unexpected end of file";
                pause();
                return;
            }

            stringstream ss(line);
            vector<string> parts;
            string part;

            while (getline(ss, part, '|')) {
                parts.push_back(part);
            }

            if (parts.size() != 10) {
                lastMessage = "Corrupted shape record";
                pause();
                return;
            }

            Shape s;
            s.id = stoi(parts[0]);
            s.type = parts[1];
            s.x = stod(parts[2]);
            s.y = stod(parts[3]);
            s.width = stod(parts[4]);
            s.height = stod(parts[5]);
            s.color.r = stoi(parts[6]);
            s.color.g = stoi(parts[7]);
            s.color.b = stoi(parts[8]);
            s.selected = (parts[9] == "1");

            loadedShapes.push_back(s);
        }

        shapes = loadedShapes;
        nextId = loadedNextId;
        lastMessage = "Shapes loaded from file";
        pause();
    }

}
