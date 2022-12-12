#include <iostream>

class IntArray{
  public:
    IntArray() = default;               // * 在有自定義建構子的情況下，內建的預設建構子會被刪除，不會被啟用。
                                        //   因此，需要透過此行寫法來啟動內建的預設建構子。
    IntArray(const IntArray& other) {
        for(int i = 0; i < N; i++){
            ele[i] = other[i];
        }
    }
    int operator[](const int& idx) const {
        int id = idx % N;
        return *(ele+id);
    }
    int& operator[](const int& idx) {
        int id = idx % N;
        return *(ele+id);
    }
    int N{5};
    int ele[5] = {0};
};

int main() {
    IntArray a;
    a[2] = 7;
    a[3] = 5;
    a[4] = 9;
    const IntArray b = a;
    std::cout << "a[7]: "  << a[7]  << std::endl   // a[7] == a[2]
              << "a[18]: " << a[18] << std::endl   // a[18] == a[3]
              << "a[25]: " << a[25] << std::endl   // a[25] == a[0]
              << "b[29]: " << b[29] << std::endl;  // b[29] == b[4]

    // Results
    // a[7]: 7
    // a[18]: 5
    // a[25]: 0
    // b[29]: 9

    return 0;
}