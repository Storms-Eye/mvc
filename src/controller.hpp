#include <std::string>

class ShapeManager
{
public:
    void handleMenuChoice();

    int readInt(const std::string &prompt)
    
    double readDouble(const std::string &prompt)
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
    std::string readstd::string(const std::string &prompt)
    {
        cout << prompt;
        std::string line;
        getline(cin, line);
        return line;
    }
    Shape *getSelectedShape()
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
    const Shape *getSelectedShape() const
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
    double computeArea(const Shape &s) const
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
    void selectShape()
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
};
