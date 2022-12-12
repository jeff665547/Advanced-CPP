// 1. 函式模板本身並不是一個函式，類別模板本身也不是一個類別，它是一個投影片母片的概念，
//    必須要設定好模板的引數後才會是一個函式或是類別，編譯器要做的事情其實就是將函式(類別)
//    模板中的參數用引數取代，並且生成一個完整功能的函式(類別)，如下方的##，為一種生成器的
//    概念，會在編譯的時候產生真正的函式(類別)。
// 2. 模板的引數必須要在編譯的時候就知道了，也因此引數不能夠使用變數，不能執行的時候才知道
//    變數的值，但唯讀變數(const T)除外，唯讀的變數因為不能被改動，所以其在編譯的時候其值
//    就會被確定下來，為唯讀運算式(constexpr)。
// 
#include <iostream>
#include <initializer_list>

template<typename T, int N> // * 這邊的typename有時會寫成class，class為早期舊式寫法。
class Array{                // * Array是類別模板的名稱(字)
public:
    Array();                // 預設建構子
    Array(const std::initializer_list<T>& l);   // 初始化列表建構子
    T& operator[](int i);       // 不唯獨的版本提供的是一個可以被更改的
    T operator[](int i) const;  // 唯獨的版本提供的是一個複製品，是不能被更改的
    int Size() const;
    T data[N];               // * 這邊的N雖然是變數，但是一定要在編譯的時候就知道N值的大小
                             //   透過模板的變數 => 在編譯時自動用const expression去取代
                             //   變數N，來參數化。
    T* begin();
    T* end();
    Array<T, N> operator+(const Array<T, N>& other);
    bool operator>(const Array<T, N>& other);
};

template<typename T, int N>
Array<T, N>::Array() {       // * Array<T, N>::Array -> 類別名稱(Array<T, N>)::函式名稱(Array)
                             // * 在編譯期使用模板參數取代的過程中，Array<T, N>::Array()實際上會自動
                             //   變成Array<t, n>::Array<t, n>()，其中t以及n是給定的引數(用來取代
                             //   參數的引數)。
    for(int i = 0; i < Size(); i++){
        data[i] = 0;
    }
}

template<typename T, int N>
Array<T, N>::Array(const std::initializer_list<T>& l) {
    int i = 0;
    for(const T& val: l) {  // * 這裡對l使用range-based for，因為initializer_list本身就支援begin以及
                            //   end語法，但不支援中括號取值，也因此不能用傳統的for迴圈。
        data[i] = val;
        i++;
    }
}

template<typename T, int N>
T& Array<T, N>::operator[](int i) {
    return data[i];
}

template<typename T, int N>
T Array<T, N>::operator[](int i) const {
    return data[i];
}

template<typename T, int N>
int Array<T, N>::Size() const {
    return N;
}

template<typename T, int N>
T* Array<T, N>::begin() {
    return &data[0];
}

template<typename T, int N>
T* Array<T, N>::end() {
    return &data[N];
}

template<typename T, int N>
Array<T, N> Array<T, N>::operator+(const Array<T, N>& other) {
    return {data[0]+other[0], data[1]+other[1]};
}

template<typename T, int N>
bool Array<T, N>::operator>(const Array<T, N>& other) {
    if(data[0] > other[0]) return true;
    if(data[0] < other[0]) return false;
    return data[1] > other[1];
}

// 使用到類別模板的函式它也要變成一個函式模板(依照不同的T以及N去產生函式)。
template<typename T, int N>
std::ostream& operator<<(std::ostream& os, const Array<T, N>& v) {
    os << "[";
    for(int i = 0; i < v.Size(); i++) {
        if(i > 0) {
            os << ", ";
        }
        os << v[i];
    }
    os << "]";
    return os;
}

template<int V = 7>
void Assign(int& O){  // Assign是函式模板的名稱(字)
    O = V;
}

/* ## */
// void Assign(int& O){  // 類別自動生成的函式
//     O = 7;
// }
template<typename T>
void Swap(T& a, T&b){
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
}

int main(){

    /* 函式模板 */
    int A = 0, B = 0;
    Assign<3>(A);  // Assign<3>才是函式的名稱(字)
    Assign<5>(B);
    Assign<4>(A);

    std::cout << A << std::endl;
    std::cout << B << std::endl;

    Swap(A, B);  // 如果函數模板的參數可以從引數去自動推導，可以省略不寫。

    /* 類別模板 */
    Array<int, 10> a;    // 類別模板的參數無法像函數模板一樣從引數推導，一定要明確地寫出來。
    Array<double, 2> b;
    
    Array<int, 5> v = {1, 2, 3, 4, 5};
    // * 此建構方式會呼叫初始化列表建構子 (initializer_list constructor)，也就是會呼叫
    //   Array<int, 5> v({1, 2, 3, 4, 5})，其中
    //   {1, 2, 3, 4, 5}的型態就是initializer_list，也就是說會去呼叫
    //   Array(const initializer_list<T>& l) {}
    // * 根據C++文件，initializer_list不支援[]索引，因此initialize的時候
    //   是使用begin以及end指標去將initializer_list內部的值一個一個拿出來使用，
    //   換句話說，只可以使用range-based for。
    // * 在此例中，因為資料成員為C風格陣列，而且是public的，所以使用初始化列表也可以透過內建的預設建構子
    //   來自動地初始化資料成員，也就是 T data[N] = {1, 2, 3, 4, 5};。
    // * 二維陣列的寫法：Array<Array<int, 2>, 2> M = {Array<int, 2>({1, 2}), Array<int, 2>({3, 4})};

    Array<int, 2> v1 = {3, 5};
    Array<double, 2> v2 = {4.5, 6.6};
    Array<int, 2> v3 = {6, 10};
    std::cout << v1 + v1 << std::endl;
    // * std::cout << v1 + v2 << std::endl; // 無法編譯，在定義類別模板中的方法時，
    //   若沒有在型別中明確寫出類別的模板參數，則代表此類別中大家使用的模板參數是一樣的，為
    //   一種自動省略的寫法：
    //   如: Array operator+(const Array& other); 實際上和下面這個寫法的意思是一樣的
    //       Array<T, N> operator+(const Array<T, N>& other);
    //   也就是代表著只有同一種類別的實例才能夠使用此運算子。

    if(v1 > v3){
        std::cout << "v1\n";
    }else{
        std::cout << "v3\n";
    }


    a[0] = 100;
    b[1] = 30.5;

    std::cout << a << std::endl;  // [0, 0, 0, 0, 0]
    std::cout << b << std::endl;  // [0, 0]

    for(auto n: a){ // ranged-based for -- 使用":"去一個個迭代
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // * range-based for 為syntax sugar會自動展開成下列程式碼 (以Array<int, 10> a為例，無const)
    //   for(int* p = std::begin(a); p != std::end(a); p++){
    //       std::cout << *p << " ";
    //   }
    //   又因為a的類別為自定義類別，因此std::begin(a)會自動去呼叫a.begin() (根據C++規定的規則)，
    //   std::end(a)同理會自動去呼叫a.end()，因此上面的程式碼又會自動展開成下列程式碼。
    //   for(int* p = a.begin(); p != a.end(); p++){
    //       std::cout << *p << " ";
    //   }
    //   其中，begin會回傳a[0]的位址，end會回傳a[a.Size()] 
    //   (也就是最後一個元素的下個元素的開頭)位址。也因此，在Array<int, 10>這個類別中，必須要去實作
    //   begin()以及end()這兩個成員函式，才能夠使用range-based for loop。
    // * 在C/C++中規定，a有a.Size()個元素，為a[0] ,..., a[a.Size()-1]，
    //   沒有a[a.Size()]這個元素(不存在此元素，不能使用)，但是有此元素的位址(存在此元素的"位址"，
    //   可以使用)，因此才能利用該位址(a[a.Size()])判斷容器是否已經被迭代完 p != a.end()。
}