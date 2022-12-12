#include <iostream>
#include <vector>
#include <algorithm>
// * 函式也是一個物件，並且支援()運算子，用()運算子運行程式，且此物件具有位址，也因此可以使用指標。
// * 函式的物件名稱(字)是全域的名稱，而且函式物件一旦建立就不可以修改內容(唯讀)，也不可以直接複製(和陣列相同)。
// * 和C風格陣列一樣，函式因為不能直接被複製，所以使用指標來儲存它的位址，用此方式讓函式在不同函式間傳遞。
// * 在C++中只有類別(用來定義物件的型態)不是個物件。
// * 函式的型態解讀：Return_type Name(Param_type); -> Name的右邊是小括弧，代表此物件是個函式(代表支援()運算)，
//   此函式的參數型態是Param_type，回傳值的型態是Return_type。
void Print() { // 定義型態為"void ()"的(函式)物件，它的名字叫 Print，"void ()"型態代表
               // 其不吃任何參數，回傳void型態(不回傳任何東西)。
    std::cout << "Hello World!";
}

// 函式模板
template<typename Compare> // 這裡的Compare可以是一種類別，可以是函式指標(透過
                           // 函式的名稱隱性轉型)，也可以是匿名函式的型態，
                           // 但是較少使用類別的方式來執行下方的任務。
int ExtremeValue(int a, int b, int c, Compare cmp) {
    int ev = a;
    if(cmp(b, ev)) {
        ev = b;
    }
    if(cmp(c, ev)) {
        ev = c;
    }
    return ev;
}

/* 自定義一般函式 */ // 函式名稱轉型類別指標
bool f(int a, int b) {
    return a > b;
}


/* 類別物件 */
class Less {
public:
    bool operator()(int, int);  // ()運算子，其接受兩個int的參數。
};

bool Less::operator()(int x, int y) {
    return x < y;
}

class Greater {
public:
    bool operator()(int, int);
};

bool Greater::operator()(int x, int y) {
    return x > y;
}

int main() {
    Print();  // Name+() => 執行()運算，得到回傳值，Name代表函式物件。
    // void (*Func)() = &Print;   // &Name，代表該函式物件的位址。型態解釋: Func是一個指標("(*Name)"的()代表
    //                            // 優先解釋，如果是"(&Name)"則代表Name是一個參考)，
    //                            // 指向一個函式(因為名稱右邊是小括弧)，此函數不吃參數(小括弧內部沒有參數型別)，
    //                            // 回傳void，這裡的Func就是函式指標。
    // 
    // (*Func)();                 // *Func會得到它所指向的目標，也就是Print物件，後面再接小括弧，就會去執行()運算。

    void (*Func)() = Print;    // * 上面的寫法目前已經被簡化成左邊的樣子(i.e. 函式的名稱(Name)可以隱性轉型成函式的位址) 
    Func();                    //   函式的指標在C++中做了延伸(繼承C)，可以直接呼叫()運算(C++會自動對函式指標取值做
                               //   dereference)。另外，函式指標與函式參考的使用方式雷同，差異不大，但函式指標應用較廣，
                               //   因其能夠放在陣列裡。

    /* 在類別中定義()operator的行為 */
    Greater g;
    Less l;

    /* Lambda匿名函式 */
    // * lambda函式為上方的方法(i.e. 使用類別定義()operator的行為)之簡化。
    // * lambda函式透過編譯器會自動產生一個相對應的類別(並且隨便取名字，類別名字並不清楚)，
    //   接著產生相應的物件(物件名稱也不清楚)。
    auto greater_lambda = [](int a, int b){  // * greater_lambda確切的類別型式並不清楚，只能使用auto。
                                             // * [...](...){...}為一個不清楚類別名稱也不清楚物件名稱
                                             //   的物件，因此被稱作匿名函式。
                                             // * 這裡是將一個不清楚類別名稱也不清楚物件名稱的物件複製給同
                                             //   類別但知道名字(greater_lambda)的物件。
        return a > b;
    };

    auto less_lambda = [](int a, int b){
        return a < b;
    };

    std::cout << std::endl;
    std::cout << "Max: " 
              << ExtremeValue(3, 7, 1, greater_lambda) << std::endl   // -> 呼叫 ExtremeValue(int, int, int, 未知的匿名函式型別) 函式
              << "Max: " 
              << ExtremeValue(3, 7, 1, f) << std::endl   // -> 呼叫 ExtremeValue(int, int, int, bool (*)(int, int)) 函式
              << "Max: " 
              << ExtremeValue(3, 7, 1, g) << std::endl   // -> 呼叫 ExtremeValue(int, int, int, Greater) 函式
              << "Min: "
              << ExtremeValue(3, 7, 1, l) << std::endl;  // -> 呼叫 ExtremeValue(int, int, int, Less) 函式
    

    std::vector<int> va = {3, 9, 1, 7, 5};
    std::sort(std::begin(va), std::end(va));  // * 因為是函式模板，所以模板參數如果可以從函數引數自動推斷的話就可以省略掉了，因此
                                              //   實際上是std::sort<std::vector<int>::iterator>(std::begin(va), std::end(va));
    for(int n: va) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::sort(std::begin(va), std::end(va), [](int x, int y) {return x > y;});  // * 第二個函式模板參數為未知的匿名函式型別

    for(int n: va) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}