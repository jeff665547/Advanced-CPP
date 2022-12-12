#include <iostream>
#include <cmath>
class Point{
  public:
    double Length() {
        return std::pow(std::pow(x, 2) + std::pow(y, 2), 0.5);
    }
    void Normalize() {
        double l = Length();
        x /= l;
        y /= l;
    }

    double x;
    double y;
};

void Normalize(Point& p) {
    double l = p.Length();
    p.x /= l;
    p.y /= l;
}

int main() {

    Point p = {3.0, 5.0}, q = {6.0, 4.0};
    Normalize(p);
    std::cout << "p: (" << p.x << ", " << p.y << "), " << p.Length() << std::endl;
    q.Normalize();
    std::cout << "q: (" << q.x << ", " << q.y << "), " << q.Length() << std::endl;

    return 0;
}