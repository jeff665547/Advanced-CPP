#include <iostream>
template<typename T>
void MySwap(T& v1, T& v2){
    T tmp;
    tmp = v1;
    v1 = v2;
    v2 = tmp;
}

void MySwap(int& v1, int& v2){
    int tmp;
    tmp = v1;
    v1 = v2;
    v2 = tmp;
}

void MySwap(double& v1, double& v2){
    double tmp;
    tmp = v1;
    v1 = v2;
    v2 = tmp;
}

void MySwap(float& v1, float& v2){
    float tmp;
    tmp = v1;
    v1 = v2;
    v2 = tmp;
}

int main() {

    int a = 1, b = 2;
    double c = 3.4, d = 5.6;
    float e = 7.8, f = 8.9;
    
    MySwap(a, b);
    MySwap(c, d);
    MySwap(e, f);

    std::cout << "a : " << a << std::endl
              << "b : " << b << std::endl
              << "c : " << c << std::endl
              << "d : " << d << std::endl
              << "e : " << e << std::endl
              << "f : " << f << std::endl;
    return 0;
}