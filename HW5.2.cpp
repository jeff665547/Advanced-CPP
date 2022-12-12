#include <iostream>

class Point{
  public:
    Point operator+(const Point& other) {
        return {x+other.x, y+other.y};
    }
    Point operator-(const Point& other) {
        return {x-other.x, y-other.y};
    }
    int x;
    int y;
};

int main() {

    Point p = {3, 5};
    Point q = {6, 4};
    Point r = p + q - p;
    std::cout << "r : (" << r.x << ", " << r.y << ")" << std::endl;

    return 0;
}