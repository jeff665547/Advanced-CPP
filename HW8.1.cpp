#include <iostream>

template<typename T, int N>
void MySort(T (&arr)[N], int start, int end) {   // 在這邊的N是屬於型態的一部分，因此不能另外透過函式參數傳入，
                                                 // 也因為是型態的一部分，必須要在編譯的時候就要確定型態，
                                                 // 不能等到執行時再做更動，也因此只能使用模板參數(泛型)的方式
                                                 // 來參數化陣列大小。
    if(start == end) return;
    // Classification
    int pivot = start;
    int indicator = pivot+1;
    for(int i = pivot+1; i < end; i++) {
        if(arr[i] < arr[pivot]) {
            std::swap(arr[i], arr[indicator]);
            indicator++;
        }
    }

    // Substitution
    indicator--;
    std::swap(arr[pivot], arr[indicator]);

    MySort(arr, start, indicator);
    MySort(arr, indicator+1, end);
}

template<typename T, int N>
void MySort(T (&arr)[N]) {       // arr 是一個參考，參考對象是一個N個元素的陣列，陣列中每個元素的型態是int。
    return MySort(arr, 0, N);
}

template<typename T, int N, typename = std::enable_if_t<!std::is_same<T, const char>::value>>
// typename = std::enable_if_t<!std::is_same<T, const char>::value> 的意思代表先去做
// 條件判斷(!std::is_same<T, const char>::value)，再來決定是否要使用此函式模版，
// 若條件回傳true，則使用此模版，否則使用其他的函式(內建or自訂皆可)。
// 如果沒有加上此條件判斷，則會造成ostream在面對std::string (i.e. const char [N], const char *)
// 資料型態的物件時，會不清楚到底是要使用內建的<<運算子函式版本，還是要使用此使用者定義的<<運算子
// 函式版本(若是使用此自訂版本會造成無窮遞迴)，造成ambiguous，但再加上此判斷式之後，ostream在面
// 對std::string的物件時就會先作條件判斷，又因條件判斷(!std::is_same<T, const char>::value)的結果
// 為false，因此會自動選擇用內建的<<運算子函式版本。
// 另一種做法是使用C++20中的concept。
std::ostream& operator<<(std::ostream& os, T (&arr)[N]) {
    os << "[";  // 此處會造成無窮遞迴(如果os << "["是使用當前的<<運算子函式而不是內建的<<運算子函式的話)。
    for(int i = 0; i < N; i++) {
        os << arr[i];
        if(i != N-1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int main() {
    int     a[3] = {7, 3, 5};
    int     b[5] = {7, 3, 9, 5, 2};
    double  c[5] = {3.1, 7.5, 4.0, 9.7, 2.5};

    MySort(a);
    MySort(b);
    MySort(c);

    std::cout << "a: " << a << std::endl
              << "b: " << b << std::endl
              << "c: " << c << std::endl;

    // Results
    // a: [3, 5, 7]
    // b: [2, 3, 5, 7, 9]
    // c: [2.5, 3.1, 4, 7.5, 9.7]

    return 0;
}