#include <iostream>

template<typename T>
class Grade{
  public:
    Grade() {
        val = default(T);    // 此代表按照T型別去做預設建構產生初始值，等價於 T{}, T()的寫法, 
                             // e.g. int -> 0, std::string -> ""
    }
    Grade(const T& input) {  // 此為一般帶有參數的建構子，或是當成轉型(T轉Grade)運算子(當input只有一個參數時才可以當)。
        val = input;         // 算是為了Grade<int> a1 = .... 而設的建構子，不可省略。
    }
    Grade operator+(const Grade& other) {
        return {val+other.val};
    }
    T val;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Grade<T>& gd) {
    os << gd.val;
    return os;
}

int main() {
    Grade<int>    a1 = 37.45,   b1 = 43.56;
    Grade<double> a2 = 37.45,   b2 = 43.56;
    std::cout << "1) " << (a1 + b1) << std::endl
              << "2) " << (a2 + b2) << std::endl;

    //  Results
    // 1) 80
    // 2) 81.01
    return 0;
}