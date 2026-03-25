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

struct Color {
    int r = 255;
    int g = 255;
    int b = 255;
};

struct Shape {
    int id = 0;
    string type;
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    Color color;
    bool selected = false;
};

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
