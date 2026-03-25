void seedData() {
        shapes.push_back({nextId++, "Rectangle", 10, 10, 40, 20, {255, 0, 0}, true});
        shapes.push_back({nextId++, "Circle", 30, 15, 25, 25, {0, 255, 0}, false});
        shapes.push_back({nextId++, "Rectangle", 5, 40, 15, 10, {0, 0, 255}, false});
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



