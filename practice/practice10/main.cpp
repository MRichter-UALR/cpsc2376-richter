// main.cpp
// Shape Manager from File
// Reads shapes from a file, creates objects using unique_ptr, and prints their areas.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

class Shape {
public:
    virtual double getArea() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double getArea() const override {
        return width * height;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}
    double getArea() const override {
        const double PI = 3.14159;
        return PI * radius * radius;
    }
};

void printAllAreas(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        std::cout << "Area: " << std::fixed << std::setprecision(4) << shape->getArea() << std::endl;
    }
}

int main() {
    std::ifstream infile("shapes.txt");
    if (!infile) {
        std::cerr << "Error: Could not open shapes.txt" << std::endl;
        return 1;
    }

    std::vector<std::unique_ptr<Shape>> shapes;
    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "rectangle") {
            double width, height;
            if (iss >> width >> height) {
                shapes.push_back(std::make_unique<Rectangle>(width, height));
            }
        }
        else if (type == "circle") {
            double radius;
            if (iss >> radius) {
                shapes.push_back(std::make_unique<Circle>(radius));
            }
        }
    }

    printAllAreas(shapes);
    return 0;
}
