#include <iostream>

void MySort(int& v1, int& v2){
    if(v1 > v2){
        int tmp = v1;
        v1 = v2;
        v2 = tmp;
        // std::swap(v1, v2);
    }
}

int main(){
    int a = 3, b = 5;
    int c = 9, d = 2;
    MySort(a, b);
    MySort(c, d);
    std::cout << "a : " << a << std::endl
              << "b : " << b << std::endl
              << "c : " << c << std::endl
              << "d : " << d << std::endl;

    return 0;
}