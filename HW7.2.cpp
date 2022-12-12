#include <iostream>

class IntArray{
  public:
    const int* begin() const {
        return ele;
    }
    const int* end() const {
        return ele+N;
    }
    int& operator[](const int& idx) {
        return *(ele+idx);
    }
    void Fill(const int& val) {
        for(auto& e: ele){
            e = val;
        }
    }
    int size() const {
        return N;
    }
    const int N = 5;
    int ele[5] = {0};  // 也可以使用 ele[N] = {0}， 
                       // 但是如果是上面的寫法，const int N = 5;
                       // 就要放到類別宣告及定義之前，並且使用全域變數了
};

std::ostream& operator<<(std::ostream& os, const IntArray& val){
    int len = val.size();
    int ct{0};
    os << "[";
    for(const int* p = val.begin(); p != val.end(); p++) {
        ct += 1;
        os << *p;
        if(ct != len) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int main() {
    IntArray a;
    std::cout << "a : " << a << std::endl;
    a.Fill(5);
    std::cout << "a : " << a << std::endl;
    a[3] = 7;
    std::cout << "a : " << a << std::endl;
    a.Fill(0);
    std::cout << "a : " << a << std::endl;

    // Results
    // a : [0, 0, 0, 0, 0]
    // a : [5, 5, 5, 5, 5]
    // a : [5, 5, 5, 7, 5]
    // a : [0, 0, 0, 0, 0]
}