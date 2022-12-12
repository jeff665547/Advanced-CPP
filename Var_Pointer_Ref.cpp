// 變數、字面常數 variables, literal constant
// 1. 變數是個有名字(稱)的物件(型態為T)，佔據記憶體空間，使用變數名稱可以取得物件值，對變數名稱做取址運算&
//    可以取得該物件的記憶體起始位址(資料型態為T*)。
//    字面常數是個沒有名字(稱)的物件，佔據記憶體空間，一旦產生就不能被改。
// 2. 字面常數與其預設資料型態： 123     => int (long, long long), 
//                             123.45  => double 
//                             123.45f => float
//                             '1'     => char
//                    字串常數  "123"   => const char[4] => 1, 2, 3, \0 => 4個元素， \0代表結尾
// 3. 顯性轉型與隱性轉型
//    * 隱性轉型：e.g. int a = 3.2;                    // 須盡量避免隱性轉型，因為會造成效能上的困擾，
//                                                    // 且會使程式碼的語意凌亂。
//                    10./3;                          // 3.33333... => 因為int轉浮點數(double或float)不會溢位
//    * 顯性轉型：e.g. int b = (int) 3.2;              // C 風格顯性轉型。
//                    int c = static_cast<int>(3.2);  // C++ 風格顯性轉型，較建議使用，可幫助查找。
// 4. 全域變數的宣告 => extern
// 5. 運算子的優先順序：先乘除後加減再去比大小，接著才去判定而且以及或者，最後才是賦值。
// 指標 pointer 與陣列 array
// 1. (C-style) pointer (Raw pointer) 指標是儲存記憶體位址的資料型態。
// 2. 指標最主要的使用場合(不得以的情況下才使用，有特殊目的)：
//    a. 變數有名字但是不能使用的情況下(因為可視範圍剛好沒有涵蓋)，可以改用位址來對此變數進行操作(如果拿的
//       到此變數的位址的話)。
//    b. 透過位址存取沒有名字的物件(如new出來的物件)。
// 3. 預期上指標是不能夠轉型的，因此如果需要指標轉型，會有很高的機率代表使用上有錯誤(void*除外)。
//    void*有點像是泛用指標的概念，可以是指向任意一種資料型態物件的記憶體位址。
// 4. 左值與右值 (lvalue & rvalue)
//    * lvalue(左值) expression: 可以做取址運算的表示式被稱作左值表示式，如:一般變數。
//    * rvalue(右值) expression: 不能做取址運算的表示式被稱作右值表示式，如:字面常數(字串除外)、暫時物件。
//    * 右值也是個物件並且也會佔據記憶體空間，只是C++規定右值表示式不能夠使用取址運算子，而這樣的設計最主要
//      的原因是要讓編譯器能在編譯(compile)的時候對程式碼進行一些優化，如:暫時物件的取代或省略之類的，假如
//      暫時物件可以取址(i.e. 假如它是左值)，就代表執行(runtime)時該暫時物件它必須要存在，因此compiler就
//      不能對該暫時物件進行取代或省略。
// 5. C語言中，函式的參數與回傳值不可以是陣列型態。C語言規定 (C-style) 陣列不可以直接複製，因為成本太高，
//    隨意複製會導致程式碼執行緩慢，如: int a[3] = {1, 2, 3}; int b[3] = a; // -> Invalid
//    但是為了讓(C-style) 陣列可以在函式間傳遞，因此C語言規定 (C-style) 陣列可以隱性轉型成其第一個元素的
//    記憶體位址，意即int a[3] = {1, 2, 3}; int* b = a;，其中b代表第一個元素的記憶體位址，即&a[0]。
// 6. 雙引號"Hello\n"在C裡面叫做字串，其形態叫做字元陣列(char[])，陣列中規定除了字串內容外，還要在最後一個
//    元素加上'\0'表示結尾，其用意為在不用知道字串長度的情況下得知此元素為字串的最後一個元素。
//    而在C中，因為陣列以及字串不能被複製(只能轉成指標(第一個元素'H'的位址))，再加上雙引號的內容不能被改變
//    (唯獨的)，也就是說字串只能轉成唯讀字元(第一個元素'H')的位址，只能使用const char*型態表達字串，
//    如: const char* str = "Hello";
//    但在C++中叫做字串常數(string literal)，使用std::string來表達字串，在C++中較常使用。
// 參考 reference
// 1. 參考其實本質不算是一種資料型態，其主要是用在初始化時用來表達別名的一種方式(只在初始化時有意義)，當
//    初始化一結束，該別名的型態就會變成是其所參考的對象之型態，
//    如: int a = {4}; int& b = a; -> 之後 b表示式 的型態為int。
// 2. 一般參考不能夠參考字面常數和暫時物件以及其他右值表示式，但是const T&可以參考右值表示式，而其意思代表
//    此參考為該右值表示式的別名，該參考和該右值表示式為同樣一個物件。
// 3. 一般參考不能夠參考不同型態的物件，如double a{2.3}; int& b = a;，但是const T&可以，編譯器會自動做隱性轉型，
//    並且參考轉型後的暫時物件，如double a{2.3}; const int& b = a;，其中，a會先經過隱性轉型成double的暫時物件，
//    接著const int& b再去參考此轉型後的暫時物件，b和轉型後的暫時物件為同一物件(b只是它的別名)。
// 4. (C-style) 陣列的元素可以是指標型別，但不能是參考型別，意即int &c[3]是不合法的。
// 5. 在C++中能參考就參考，能唯讀就唯讀，可以進一步地提升效能。

#include <iostream>
void f(int* b){ // 此為陣列傳進function的方式(以pointer格式)。所有f(int b[12]), f(int b[999]), f(int b[N]), 
                // f(int b[]), ... 都可以編譯成功並且執行，因為上述格式到最後皆會被編譯器替代為f(int* b)，
                // 亦即上面的格式全部等價。C語言中，函式的參數跟回傳值不可以是陣列型態，因為陣列不能複製。
                // 因此，陣列傳進function是將a陣列隱形轉型成&a[0]，以f(int* b = &a[0])的方式傳入函式，也就是說
                // 在使用端的程式碼，寫f(a)以及f(&a[0])的意思是一樣的。
                // 同樣原理，f(int b[][])事實上就是f(int** b)。
}

void g(int (&b)[3]){  // 在此例中，陣列傳入funtion是直接傳入，也就是說g(int (&b)[3] = a)，此時，參考物件的陣列大小[3]
                      // 也變得有意義，若陣列大小不一致，則無法成功地reference，會被視為不同型態。換句話說，透過此方式，
                      // a和b在function中是指同樣的一個物件，不再是pointer。在C++中主要使用此種方式來傳遞C-style陣列。
}

int main() {

    int baa = 5;
    baa = baa << 3; // * 將baa向左邊位移3個位元，也就是 5*2*2*2 = 5*(2^3) = 40。
    std::cout << baa << std::endl;

    /* Initialization */
    int ina = 7;        // * C風格就支援的初始化。
    // int ina = {7};   // * C++風格支援的初始化，和下方意思一樣。
    // int ina{7};      // * C++風格支援的初始化。
    int inb{7.3};  // * 編譯錯誤，大括弧會檢查有沒有造成資訊量的損失，有損失就會報錯誤，如此例。
    std::cout << "sizeof(baa): " << sizeof(baa) << std::endl;  // * sizeof 運算子可以計算物件所占記憶體大小(位元組)。
    int inaa, inbb, incc;
    inaa = inbb = incc = 9;  // * 賦值運算子 = 的優先順序是由右至左 (先對incc做賦值，接著得到incc，接著再將incc給inbb做賦值，...)
    std::cout << inaa << ", " << inbb << ", " << incc << std::endl; // 9, 9, 9
    const int cina = 9; // * 在程式中，能加const就加const，因為其可以保證cina在別處被使用時值能不會發生改變，如果沒有加上const
                        //   的話，就必須在下一次被使用之前去一一地檢查程式碼，查看其有沒有被修改，也就是說使用const夠增加閱讀以及撰寫
                        //   程式碼的效率。
    int pa = 0;
    int pb;
    pb = ++pa;  // => 回傳pa加1之"後"的值
    pb = pa++;  // => 回傳pa加1之"前"的值
    pa = pa++;  // => 未定義行為 (在同一句statement中給了pa兩種不同的值)
    pa = ++pa;  // => 可編譯 (在同一句statement中給了pa同樣的值)

    int ia;   // => 未定義行為(Undefined behavior!!) 此時的ia可能是0或1或是其他種可能。
    // &&ia;  // Invalid: &ia means the address of the a object, and it's a temporary object. 
             // The temporary object is a rvalue expression, so it cannot use the & operator.
             // i.e. &(&ia) => &&ia is invalid.

    ia = 3;
    int& ib = ia, ic = ib, id = ic;
    // int& iv[3] = {ib, ic, id}  // Invalid: The type of the elements of the (C-style) array cannot be 
                                  //          the reference, but it can be the pointer. (C++規定)

    int* ipa = &ia;
    *ipa = 9999;  // 相當於是ia = 9999;  *(&ia) = 9999;  => ia = 9999;
    std::cout << ia << std::endl;

    const int& aa = 3;        // Valid: literal constant
    const int& bb = aa + 1;   // Valid: temporary object

    double da{2.3}; 
    // int& db = da;     // Invalid
    const int& ie = da;  // Valid: const reference the temporary object that is implicitly converted from the 
                         // da.

    int a[3] = {1, 2, 3};  // 陣列的初始化，和下方初始化方式(省略等號)相同。
    int arrb[3] {1, 2, 3};
    // int b[3] = a;        // Invalid: C-style array cannot be copied (by C spec def), since the high cost.
    int* b = a;             // Valid: a -> Implicitly convert to &a[0] (temporarily object) 
                            //          -> Copy the temporarily object &a[0] to b (Copy constructor of int*).
                            //          The expression means an int pointer b.

                            // 資料型態的解讀：解釋資料型態時，以名字(稱)當中心，以名字右邊先解釋，解釋完右邊再看左邊，
                            // e.g. int c[3] => c右邊是中括號，意味著是個陣列，也就是說c是一個{陣列，該陣列有3個元素，
                            // 每個元素}是個整數。
                            // int c => c右邊沒東西，意味著c是一個{}是個整數，也就是說c是一個整數。
                            // int &c[3], int& c[3] 一樣意思 => c右邊是中括號，意味著是個陣列，也就是說c是一個
                            // {陣列，該陣列有3個元素，每個元素}是個(c的左邊)參考，參考一個整數 
                            // => Invalid by C++ spec def，陣列裡面不能放參考。
                            // int (&c)[3] => c外圍有小括號，優先判讀。c是一個參考，參考一個陣列，該陣列有3個元素，
                            // 每個元素是個整數。
    int (*c)[3] = &a;       // Valid: An array (of size 3) pointer c. (i.e. A pointer which points to an array (of size 3).)
    int (&d)[3] =  a;       // Valid (C++ only): A reference (d) to an array of size three. (d is an alias of a).

    f(a);
    g(a);

    for(int i = 0; i != 3; i++){
        std::cout << b[i] << std::endl;     // b[i] -> *(b+i) -> *(&a[0]+i) -> *(&a[i]) -> a[i]
    }                                       // C語言規定 x[y] => *(x+y), 
                                            // C語言規定陣列元素的位址可以加減一個整數取得另一個元素的位址 (&a[i]+j => &a[i+j])。
                                            // C語言規定陣列型態可以隱性轉型成其第一個元素型態的指標 (a => &a[0])

    for(int i = 0; i != 3; i++){
        std::cout << (*c)[i] << std::endl;  // dereferenced c -> c == &a, *c == *&a, *c == a. -> (*c)[i] == a[i]
    }

    for(int i = 0; i != 3; i++){
        std::cout << d[i] << std::endl;     // d[i] == a[i] (C++ only)
    }

    for(auto v: {1, 2, 3}) {
        std::cout << v << std::endl;
    }

    int iaa, ibb, icc;
    iaa = ibb = icc = 1;
    // std::cout << iaa == ibb == icc << std::endl;  // 編譯錯誤： "<<" 的優先程度高於 "=="

    int zaa = 3;
    const int zbb = 5;
                            // 可否執行        行為
    const int  zcc1 = zaa;  //    O       zaa 會被複製給 zcc1 (zaa會先被轉型為const int(不會產生新物件
                            //            (概念類似檔案讀取權限，直接再zaa先暫時加上唯讀)) 再將內容複製給 zcc1)
    int        zcc2 = zaa;  //    O       zaa 會被複製給 zcc2 (zaa會直接將內容直接複製給zcc2)
  
    const int  zcc3 = zbb;  //    O       zbb 會被複製給 zcc3 (zbb會直接將內容直接複製給zcc3)
    int        zcc4 = zbb;  //    O       zbb 會被複製給 zcc4 (zbb會直接將內容直接複製給zcc4 
                            //                                const int無法在不產生新物件的條件下轉型成int)
  
    const int& zdd1 = zaa;  //    O       zaa的值不可以透過zdd1來更動，但zaa本身可以更動(zdd1是zaa的別名)
                            //            (zaa會先被隱性轉型為const int(不會產生新物件
                            //            (概念類似檔案讀取權限，直接再zaa先暫時加上唯讀)) 再將內容給 zdd1參考)
    int&       zdd2 = zaa;  //    O       zaa的值可以透過zdd2來更動，且zaa本身也可以更動(zdd2是zaa的別名)
  
    const int& zdd3 = zbb;  //    O       zbb的值不可以透過zdd3來更動，且zbb本身也不可以更動(zdd3是zbb的別名)。
    // int&      zdd4 = zbb;//    X       編譯錯誤：zbb本身不可以更動，因此zdd4與zbb必須具有相同型態(不可以更動、唯讀)，
                            //                     才能讓zdd4去當zbb的別名，(zdd4才能去參考abb)。
    return 0;
}