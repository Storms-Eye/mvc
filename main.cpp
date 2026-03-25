// main.cpp
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


class ShapeManagerApp {
private:
    vector<Shape> shapes;
    int nextId = 1;
    bool running = true;
    string lastMessage = "Welcome to Shape Manager";

public:
    void run() {
        seedData();

        while (running) {
            clearScreen();
            drawHeader();
            drawShapes();
            drawMenu();
            handleMenuChoice();
        }
    }

private:
    void seedData() {
        shapes.push_back({nextId++, "Rectangle", 10, 10, 40, 20, {255, 0, 0}, true});
        shapes.push_back({nextId++, "Circle", 30, 15, 25, 25, {0, 255, 0}, false});
        shapes.push_back({nextId++, "Rectangle", 5, 40, 15, 10, {0, 0, 255}, false});
    }

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
             << setw(12) << "Type"
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

    void handleMenuChoice() {
        int choice = readInt("Enter choice: ");

        switch (choice) {
            case 1:
                addShape("Rectangle");
                break;
            case 2:
                addShape("Circle");
                break;
            case 3:
                selectShape();
                break;
            case 4:
                moveSelectedShape();
                break;
            case 5:
                resizeSelectedShape();
                break;
            case 6:
                recolorSelectedShape();
                break;
            case 7:
                deleteSelectedShape();
                break;
            case 8:
                showStatistics();
                break;
            case 9:
                saveToFile();
                break;
            case 10:
                loadFromFile();
                break;
            case 11:
                sortShapesByArea();
                break;
            case 12:
                searchByType();
                break;
            case 13:
                clearAllShapes();
                break;
            case 14:
                running = false;
                lastMessage = "Exiting program";
                break;
            default:
                lastMessage = "Invalid menu choice";
                pause();
                break;
        }
    }

    int readInt(const string& prompt) {
        while (true) {
            cout << prompt;
            string line;
            getline(cin, line);

            stringstream ss(line);
            int value;
            char extra;

            if (ss >> value && !(ss >> extra)) {
                return value;
            }

            cout << "Invalid integer input. Try again.\n";
        }
    }

    double readDouble(const string& prompt) {
        while (true) {
            cout << prompt;
            string line;
            getline(cin, line);

            stringstream ss(line);
            double value;
            char extra;

            if (ss >> value && !(ss >> extra)) {
                return value;
            }

            cout << "Invalid numeric input. Try again.\n";
        }
    }

    string readString(const string& prompt) {
        cout << prompt;
        string line;
        getline(cin, line);
        return line;
    }

    Shape* getSelectedShape() {
        for (auto& s : shapes) {
            if (s.selected) {
                return &s;
            }
        }
        return nullptr;
    }

    const Shape* getSelectedShape() const {
        for (const auto& s : shapes) {
            if (s.selected) {
                return &s;
            }
        }
        return nullptr;
    }

    double computeArea(const Shape& s) const {
        if (s.type == "Rectangle") {
            return s.width * s.height;
        }
        if (s.type == "Circle") {
            double radius = s.width / 2.0;
            return 3.14159265358979323846 * radius * radius;
        }
        return 0.0;
    }

    void addShape(const string& type) {
        double x = readDouble("Enter x position: ");
        double y = readDouble("Enter y position: ");
        double w = readDouble("Enter width: ");
        double h = readDouble("Enter height: ");

        if (w <= 0 || h <= 0) {
            lastMessage = "Width and height must be positive";
            pause();
            return;
        }

        int r = readInt("Enter color R (0-255): ");
        int g = readInt("Enter color G (0-255): ");
        int b = readInt("Enter color B (0-255): ");

        r = clampColor(r);
        g = clampColor(g);
        b = clampColor(b);

        for (auto& s : shapes) {
            s.selected = false;
        }

        Shape s;
        s.id = nextId++;
        s.type = type;
        s.x = x;
        s.y = y;
        s.width = w;
        s.height = h;
        s.color = {r, g, b};
        s.selected = true;

        if (type == "Circle") {
            s.height = s.width;
        }

        shapes.push_back(s);
        lastMessage = type + " added and selected";
        pause();
    }

    void selectShape() {
        if (shapes.empty()) {
            lastMessage = "No shapes available to select";
            pause();
            return;
        }

        int id = readInt("Enter shape ID to select: ");
        bool found = false;

        for (auto& s : shapes) {
            s.selected = false;
            if (s.id == id) {
                s.selected = true;
                found = true;
            }
        }

        lastMessage = found ? "Shape selected" : "Shape ID not found";
        pause();
    }

    void moveSelectedShape() {
        Shape* s = getSelectedShape();
        if (!s) {
            lastMessage = "No selected shape to move";
            pause();
            return;
        }

        double dx = readDouble("Enter delta x: ");
        double dy = readDouble("Enter delta y: ");

        s->x += dx;
        s->y += dy;

        ostringstream msg;
        msg << "Moved shape " << s->id << " to (" << s->x << ", " << s->y << ")";
        lastMessage = msg.str();
        pause();
    }

    void resizeSelectedShape() {
        Shape* s = getSelectedShape();
        if (!s) {
            lastMessage = "No selected shape to resize";
            pause();
            return;
        }

        double newW = readDouble("Enter new width: ");
        double newH = readDouble("Enter new height: ");

        if (newW <= 0 || newH <= 0) {
            lastMessage = "Width and height must be positive";
            pause();
            return;
        }

        s->width = newW;
        s->height = (s->type == "Circle") ? newW : newH;

        lastMessage = "Selected shape resized";
        pause();
    }

    void recolorSelectedShape() {
        Shape* s = getSelectedShape();
        if (!s) {
            lastMessage = "No selected shape to recolor";
            pause();
            return;
        }

        int r = readInt("Enter new R (0-255): ");
        int g = readInt("Enter new G (0-255): ");
        int b = readInt("Enter new B (0-255): ");

        s->color.r = clampColor(r);
        s->color.g = clampColor(g);
        s->color.b = clampColor(b);

        lastMessage = "Selected shape color updated";
        pause();
    }

    void deleteSelectedShape() {
        auto it = remove_if(shapes.begin(), shapes.end(), [](const Shape& s) {
            return s.selected;
        });

        if (it == shapes.end()) {
            lastMessage = "No selected shape to delete";
            pause();
            return;
        }

        shapes.erase(it, shapes.end());

        if (!shapes.empty()) {
            shapes.front().selected = true;
        }

        lastMessage = "Selected shape deleted";
        pause();
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

    void sortShapesByArea() {
        sort(shapes.begin(), shapes.end(), [this](const Shape& a, const Shape& b) {
            return computeArea(a) < computeArea(b);
        });

        lastMessage = "Shapes sorted by area";
        pause();
    }

    void searchByType() {
        clearScreen();
        drawHeader();

        string query = readString("Enter type to search for: ");
        for (char& c : query) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }

        cout << "\nSearch Results\n";
        cout << "--------------\n";

        int matches = 0;
        for (const auto& s : shapes) {
            string typeLower = s.type;
            for (char& c : typeLower) {
                c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            }

            if (typeLower.find(query) != string::npos) {
                cout << "ID " << s.id << ": " << s.type
                     << " at (" << s.x << ", " << s.y << ")\n";
                matches++;
            }
        }

        if (matches == 0) {
            cout << "No shapes matched the search.\n";
        }

        pause();
        lastMessage = "Search complete";
    }

    void clearAllShapes() {
        string confirm = readString("Type YES to clear all shapes: ");
        if (confirm == "YES") {
            shapes.clear();
            lastMessage = "All shapes cleared";
        } else {
            lastMessage = "Clear operation canceled";
        }
        pause();
    }

    int clampColor(int value) {
        if (value < 0) return 0;
        if (value > 255) return 255;
        return value;
    }

    void pause() {
        cout << "\nPress Enter to continue...";
        string dummy;
        getline(cin, dummy);
    }
};

int main() {
    ShapeManagerApp app;
    app.run();
    return 0;
}
