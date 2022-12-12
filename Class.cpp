// 1. 類別可以把其宣告以及定義給分開，但要產生此類別類型的物件必須要先定義好此類別
//    i.e. 產生類別物件的語法要寫在此類別定義之後。
// 2. 在類別內部的成員(變數資料及函式)先後宣告及定義順序是可以顛倒的，沒有固定順序。
// 3. 成員函式的宣告以及定義可以分開，若分開，成員函式的定義必須寫在類別的外面。
// 4. 類別宣告(e.g. class Point;)以及定義(e.g. class Point{};)必須要在該類別的
//    物件產生之前完成，若類別只有宣告，是不能夠拿該類別的宣告去產生物件，因為
//    compiler會不清楚物件的大小會有多大。
#include <iostream>
#include <cmath>
#include <cstdio>

class Point;   // 類別宣告以及定義分開

class Point{   // {}內是類別的可視範圍(class scope)，而此類別名字(Point)的可視範圍是全域的。
  public:
    int x;
    int y;
    double Length();  // 成員函式的宣告以及定義分開
    Point Add(Point) const;  // 這邊的const是用來修飾此成員函式，代表此函式除了可以在一般物件呼叫外，
                             // 還可以在唯讀物件進行呼叫，一般物件可以透過隱性轉型成唯讀物件再呼叫此函式
                             // (一般物件會優先呼叫沒有唯讀的版本，如果沒有此版本的函式才會進行隱性轉型
                             //  成唯讀物件並且呼叫此函式)。
                             // (這個被叫做唯讀的轉型)
                             // 這裡的const其實是代表在成員函式中參數項被隱藏起來的const Point* this，
                             // 代表this指標所指的Point物件是唯讀的，不能被更動的。 
                             // 成員函式宣告時，參數名稱可以被省略 (包含各式建構子以及運算子)。
    // const Point Add(Point rhs);  // 這邊的const是用來指回傳的結果是唯讀的，不希望使用者去更改回傳後的物件，
                                    // 如：p.Add(q).Clear() => 就設計角度而言，這樣的寫法是不符合語法(因為
                                    // Clear() 沒有const修飾)且毫無意義、不合理的，因為Clear()的對象是p和q相
                                    // 加後所生成的暫時物件，不是去清理任何一個現存的物件。
                                    // 也因此，透過在回傳值進行const修飾來對此類寫法進行約束，讓此問題在設計
                                    // 程式時就被凸顯提醒，要做Clear()前，先將此計算結果先用變數給存起來。
                                    // 在多數情況下，其實不太需要在回傳值加上const修飾，有使用const修飾的話通常會
                                    // 用來修飾指標以及參考類型的回傳值並與傳入的參數型態一起搭配著使用，如：
                                    // const int& f(const int& b) {return b;} -> 見下方解說。
    
    // const int& f(const int& b) {  // 當我們希望傳入的引數不要被f函式進行更改時，參數型態會使用const T&
    //                               // 若要回傳和參數相同的變數，則回傳值型態會跟傳入的參數型態一致。
    //                               // 另一種使用const T&的情況是傳入的引數是rvalue的時候會使用到。
    //        ...            // Do Something with b ...
    //     return b;
    // } 
    void Clear() {
        x = y = 0;
    }
    Point operator+(const Point& rhs) const {
        return {x + rhs.x, y + rhs.y};  // 回傳Point{x + rhs.x, y + rhs.y}，為一個暫時物件
    }
};

Point Add(Point lhs, Point rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};  // 用大括弧來初始化回傳值。
}

// Point operator+(const Point& lhs, const Point& rhs) {
//     return {lhs.x + rhs.x, lhs.y + rhs.y};
// }

// 定義一個空的類別。
class Test{
  // 在一個甚麼都沒有寫的空類別中，C++會自動產生一個預設版本的預設建構子，也就是下方的寫法：
  // public:
  //   Test() = default;   // default就是預設版本的預設建構子。 // delete就是刪除預設版本的預設建構子。
};

// Test 的預設建構子，內建本身就會提供，但如果有自己的定義則編譯器會優先採用。
// 類別名稱::函式名稱
// Test::Test() {} // 不能有回傳值型態

class One{
  public:
    int val;   // * 如果此處是 int val = 1; 則代表使用One類別的預設建構子時，會自動將val設值為1，
               //   同時，如果是使用帶有參數的一般建構子(同樣也是去設定val的值)，則會將val的值給
               //   覆蓋過去，即使val已經有預設的值了。建議在各個建構子中分別設定資料成員的值
               //   (包含在預設建構子也是這樣操作)，不建議在此處寫int val = 1;，這樣會比較清楚。
    One() {                                          // 產生物件: 1. 配置記憶體  2. 呼叫建構子
        std::cout << "One::One()" << std::endl;     
    }
    ~One() {                                         // 刪除物件: 1. 呼叫解構子  2. 釋放記憶體
        std::cout << "One::~One()" << std::endl;
    };
};

class OutputStream{
  public:
    OutputStream& operator<<(const char* s){
        printf("%s", s);
        return *this;
    }
};

class Grade{
    friend Grade operator+(const Grade& p, const Grade& q);  // * 設定成好友，讓別的好友函式也可以直接讀取
                         // 或是更改私有資料成員。沒被設成好友的函式或是類別只能透過好友函式或是類別來讀取或是
                         // 更改私有成員。friend算是去針對存取限制(也就是封裝的核心：允許的才能夠被使用，不允
                         // 許的就不能被使用)開通例外，friend不會受到放在public或是private範圍的影響，其意思
                         // 都是一樣的。
  
  public:                // * 一般來說，公開的成員越少越好。

    Grade(int val) {     // * 若有定義一般的建構子(帶有參數的建構子、直接建構子)，則compiler不會自動幫我們加上
                         //   預設建構子。
        this->val = val; // * 當參數與資料成員撞名時，使用this->來表達物件自己本身(即&self)
    }                    // * 單一參數的建構子意味著支援將int物件複製並且隱性轉型成Grade型態的物件。
    // * 底下為初始化序列的寫法(下面寫法和上面是等價的，但下面的效能較高，因為少了this->val=val;中的複製賦值運算，
    //   在此處中的val(val)屬於int的直接建構(direct initialization)，沒有再使用到複製賦值運算，然而上面的語意是
    //   先對val預設建構一次，再使用int的複製賦值運算賦予給定的值，多一層手續。) (初始化序列的寫法可以避免使用this)。
    // Grade(int val) val(val) {}

    // Grade operator+(const Grade& other){  // * 一般來說會使用底下global function (operator+(...))
    //     return {val+other.val};           //   的寫法較為泛用
    // }
    int getVal() const {
        return val;      // * Getter: 讓使用者拿到複製品，不要更改到本身物件裡的成員值。物件導向的寫法較傾向於使用
                         //           此用法，而不是使用friend，friend的用法對物件導向來說較不乾淨。
    }
  private:                                        // * 私有成員的存取限制是以類別為單位的。只要是在與此私有成員同類別
                                                  //   的成員函式都可以直接使用此私有成員，即便該成員函式是對同類別的
                                                  //   不同物件進行操作也是可以直接取用該物件的私有成員，因為是以
                                                  //   類別為單位。
    int val;
};

Grade operator+(const Grade& p, const Grade& q){
    return {p.val + q.val};
}

class IntArray5{
public:
  int& operator[](int i) {             // 回傳不唯獨參考可透過參考去改IntArray5內部的資料。
    return val[i];
  }
  const int& operator[](int i) const { // 唯讀的物件呼叫此函式，因為呼叫此函式的物件是唯讀的，
                                       // 所以它的成員也都是唯讀的，因此此函式再回傳時只能夠考慮
                                       // 複製一份新的(T)，或是回傳唯讀的參考(const T&)(效率較好)。
    return val[i];
  }
  int val[5];
};

void f(const IntArray5& p) {}

int main(){

    // 可以用初始化串列 {} 初始化類別物件的公開資料成員，
    // {}內的元素會一個個去對應類別中的成員做初始化。
    Point p = {3, 5};
    Point q{6, 4};
    std::cout << p.Length() << std::endl;
    Point r = Add(p, q);
    Point s = p + q;    // Compiler 在看到此statement以後，會自動呼叫以下兩個function的其中一個function
                        // (看底下兩種是哪一種有實作出來，如果兩種都沒有實作或是兩種(or 以上)都有實作
                        // (compiler ambiguous)的話 => 編譯失敗)
                        // p+q -> operator+(p, q) => operator+(const Point&, Const Point&)
                        // p+q -> p.operator+(q) => Point::operator+(const Point&) const

    const Point pp = {0, 8};

    // 空類別原則上就只能做到下列幾件事情：
    Test t1;       // 空類別Test的預設初始化：沒給初始值的情況下建構物件(呼叫預設建構子Test::Test() <- 預設建構子一定不能吃參數(不給初始值)，
                   // 且內建的預設(default)版本不會幫我們做任何成員賦值的動作，也就是說不會做任何事情。)
                   // --> 此行指令做了兩件事：1. 配置一個記憶體空間(根據類別的內容給定記憶體大小)產生物件。 2. 呼叫Test的(內建 or 自訂)預設建構子。

    Test t2 = t1;  // 空類別Test的複製初始化：用同型態物件初始化新的物件(使用複製的方式，呼叫複製建構子Test::Test(const Test&)，內建的預設版本
                   // (default)是去將資料成員都進行一次複製，這邊一定要使用參考的原因是因為，如果不使用參考就會導致參數在使用引數來做初始化時會
                   // 觸發複製建構子，進而造成無窮遞迴)，Test t2 = t1的寫法等同於Test t2(t1)以及Test t2{t1}。

    t2 = t1;       // 空類別Test的複製賦值運算：複製賦值同型態物件到已有物件(呼叫複製賦值運算函式Test& Test::operator=(const Test&)，
                   // 內建的預設版本(default)是去將資料成員都進行一次複製，這邊回傳參考主要的目的是要讓此運算的結果可以接著使用，達成串流式用法，
                   // 如cout的 << 運算子。以及讓別的同類型變數可以接下去進行參考初始化，如下例，如果回傳類型行為非參考的類型，則會在回傳時"複製"
                   // 產生一份暫時物件，如此一來就不能被一般的參考所參考)。

    Test& t3 = t2 = t1;  // 空類別Test參考的初始化：參考同型態物件。一般的運算子(如<<)的運行順序是由左到右運行，而等號運算子是從最右邊先做再到最左邊，
                         // 此寫法中的t2 = t1是做複製賦值運算，並且回傳t2自己(*this)，Test& t3 = t2則是一般參考的初始化。

    std::cout << sizeof(Test) << " " << sizeof(t1) << std::endl;  // 空類別的物件其佔記憶體最小一個byte
                                                                  // (因為必須是實體物件，可以被取位址，
                                                                  // 因此以使用一個最小的記憶體size來表達)

    Test();         // 類別名稱加上()的語法規定利用預設初始化產生該類別的暫時物件。=> 當我們執行到下一行時，暫時物件的生命週期就結束了。
    // Test t4();   // <- 左邊此寫法是行不通的，會被視為一個新的函式宣告，會把t4解釋成是一個函式，而非一個物件
                    // 易和t1的預設建構方式搞混。

    One oa;                            // 呼叫預設建構子
    std::cout << oa.val << std::endl;  // 此為未定義行為，因為val沒有被設初始值。

    /* 在有printf的條件下自定義cout */
    OutputStream cout;
    cout << "Hello world!\n";  // Compiler會自動去呼叫下面兩種函式裡的其中一個函式。
                               // 1. operator<<(cout, "Hello world!");
                               // 2. cout.operator<<("Hello world!"); -> OutputStream::operator<<(const char*);
                               // 在 std::cout 中，因為我們不能夠去更改std::cout的類別定義，因此，為了讓自訂的類別可以
                               // 使用std::cout，我們會以第1種函式來替自訂類別定義使用std::cout的行為。

    /* 物件的初始化 */
    // Default Initialization 預設初始化 => 呼叫預設建構子(不傳任何參數) => 一般會歸零(依據資料類型)，
    //                                                                             如int: 0, std::string: ""
    int iaaa;
    // Value Initialization   值初始化 => 呼叫預設建構子(不傳任何參數) => 一般會歸零(依據資料類型)，
    //                                                                           如int: 0, std::string: ""
    int a{};
    int{};
    // Zero Initialization    零初始化 (部分的值初始化也被稱作零初始化，如上面的兩個例子)
    // Direct Initialization  直接初始化  => 呼叫帶有參數的直接建構子 (在類別中有直接建構子就不會有內建的預設建構子，
    //                                                              如果兩者皆須存在，需要額外手動指明預設建構子
    //                                                              (default))
    int ii(3);
    // Copy Initialization    複製初始化  =>  呼叫複製建構子
    int ibbb = iaaa;
    // Reference Initialization 參考初始化  =>  不會呼叫任何建構子
    // List Initialization    初始化列表初始化: 使用{}初始化且其中帶有一個以上元素時
       // Direct-List Initialization 直接列表初始化  => 呼叫帶有參數的建構子
       Point pp2{3, 5};
       Point{1, 2};
       // Copy-List Initialization   複製列表初始化  =>  呼叫複製建構子
       Point pp3 = {3, 5};

    Grade g = 10;  // => 呼叫 Grade g(10) => Grade::Grade(int); 直接初始化

    g + 20;  // call Grade::Grade(int) 隱性轉型 => call Grade::operator+(const Grade&)

    40 + g;  // call int::operator+(const Grade&) -> (X) 
             //      or operator+(int, const Grade&) -> (O) Self-defined function extension
             //      or operator+(const Grade&, const Grade&)
             // 若以物件導向的方式看待，此時的40不能夠隱性轉型成Grade，並且產生Grade的暫時物件
             // 也就是不能使用Grade::Grade(int)。但卻可以在使用函式時隱形轉型成Grade，產生暫時物件
             // 也就是說可以在operator+(const Grade&, const Grade&)時先使用Grade::Grade(int)轉型。

    IntArray5 A;
    A[1] = 3;  // * a[1] => Operator overloading => a.operator[](1) (只會呼叫這種函式，沒有一般函式的版本)
    A[3] = 7;

    const IntArray5 B = A;  // * 透過自定義類別將C風格陣列給包起來的好處 => 可以透過複製建構子直接複製資料成員(也就是C風格陣列)
    A[1] = 9;

    std::cout << A[1] << std::endl;  // 9   => 呼叫IntArray5::operator[](int)的版本。
    std::cout << A[2] << std::endl;  // 7

    std::cout << B[1] << std::endl;  // 3   => 呼叫IntArray5::operator[](int) const的版本。
    std::cout << B[2] << std::endl;  // 7

    f(A);   // * 在這邊的f可以選擇使用複製(T)的方式或是參考(const T&)的方式來對其參數進行初始化(C++的寫法)，
            //   有別於在函式中直接傳遞C風格陣列不能直接複製，只能隱性轉型並且傳遞陣列中第一個元素的記憶體位址。
            //   在此處，我們透過自定義類別的方式將C風格陣列給包成資料成員，利用類別以及物件的特性來在函式間傳遞。

    return 0;
}

// 完整名字 = 類別名稱::函式名稱
double Point::Length() {  // Point::Length為此方法之全名，而Point::與命名空間的概念相同。
    return sqrt(x*x + y*y);
}

Point Point::Add(Point rhs) const {
    return {x+rhs.x, y+rhs.y};  // C++11
}