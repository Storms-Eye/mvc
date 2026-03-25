#include "controller.hpp"

void ShapeManager::handleMenuChoice()
{
    int choice = readInt("Enter choice: ");

    switch (choice)
    {
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

int ShapeManager::readInt(const string &prompt)
{
    while (true)
    {
        cout << prompt;
        string line;
        getline(cin, line);

        stringstream ss(line);
        int value;
        char extra;

        if (ss >> value && !(ss >> extra))
        {
            return value;
        }

        cout << "Invalid integer input. Try again.\n";
    }
}

double ShapeManager::readDouble(const string &prompt)
{
    while (true)
    {
        cout << prompt;
        std::string line;
        getline(cin, line);

        std::stringstream ss(line);
        double value;
        char extra;

        if (ss >> value && !(ss >> extra))
        {
            return value;
        }

        cout << "Invalid numeric input. Try again.\n";
    }
}

std::string ShapeManager::readstd::string(const std::string &prompt)
{
    cout << prompt;
    std::string line;
    getline(cin, line);
    return line;
}

Shape *ShapeManager::getSelectedShape()
{
    for (auto &s : shapes)
    {
        if (s.selected)
        {
            return &s;
        }
    }
    return nullptr;
}

const Shape *ShapeManager::getSelectedShape() const
{
    for (const auto &s : shapes)
    {
        if (s.selected)
        {
            return &s;
        }
    }
    return nullptr;
}

double ShapeManager::computeArea(const Shape &s) const
{
    if (s.type == "Rectangle")
    {
        return s.width * s.height;
    }
    if (s.type == "Circle")
    {
        double radius = s.width / 2.0;
        return 3.14159265358979323846 * radius * radius;
    }
    return 0.0;
}

void ShapeManager::selectShape()
{
    if (shapes.empty())
    {
        lastMessage = "No shapes available to select";
        pause();
        return;
    }

    int id = readInt("Enter shape ID to select: ");
    bool found = false;

    for (auto &s : shapes)
    {
        s.selected = false;
        if (s.id == id)
        {
            s.selected = true;
            found = true;
        }
    }

    lastMessage = found ? "Shape selected" : "Shape ID not found";
    pause();
}
void ShapeManager::searchByType() {
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

}

