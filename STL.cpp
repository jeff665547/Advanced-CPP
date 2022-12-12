// 0. 文件查找流程
//    a. 先從quick start之類的東西快速兜一個簡單範例，越接近實際使用情況越好，
//       或是直接試著使用看看，看結果表現是否和預期有差別，並且透過拆解成小問題、
//       心智圖聯想法、去猜猜看，或是上網查找有無可能的解決方法。
//    b. 如果不行的話再查閱說明書以及文件(SDK)，尋找有無漏掉的步驟或是觀念。
//    c. 先看懂自己會的東西的文件，在利用類似的邏輯去看自己不會的東西的文件，不需
//       要把文件上所有的字都看過(不會有人這樣做)，找重要的資訊即可。
// 1. 以std::string為例(文件查找)
//    0. 文件中的右上角標示<string>代表此類別相關資訊存放在該檔案裡，要使用時要
//       加上#include <string>才能使用該類別。
//    1. 文件中的typedef basic_string<char> string;代表string是
//       basic_string<char>的別名。(對basic_string<char>取別名的意思)
//    2. 對類別來說，我們要看成員函式(member function)列表來了解該類別物件所支援
//       的操作。
//    3. 在constructor的頁面中，最上方的std::string::string的意思代表
//       命名空間::類別名稱::成員函式名稱，因為為建構子(string)，所以成員函式名稱
//       也是string。
//    4. 選擇C++的使用版本，如:C++11
//    5. e.g. 預設建構子 default string();  使用方式為 string s;  -> 不吃任何引數參數
//       e.g. 一般建構子 from c-string string(const char* s);  
//            使用方式為 string s = "Hello World!";  -> 從C風格字串建構
//       e.g. 複製建構子 string (const string& str);
//            使用方式為 string s = "Hello World!";
//                      string t = s;  -> 從其他已經存在的字串變數建構
//                      string u(s);   -> 從其他已經存在的字串變數建構
//    6. 在一般成員函式的頁面中，查看其重要資訊
//       如：回傳值, 參數型態, const的位置, ... 等
//       e.g. size_t size() const noexcept;  ->  代表此函式回傳size_t，而且
//            const string物件也可以使用，noexcept表示該函式不會拋出例外。另外，
//            在同頁面下方的"回傳值"欄位會介紹回傳值型態，即size_t為一種非負整數，
//            相當於unsigned int。
//       e.g. operator[] 有兩種版本(有無const)
//            char& operator[] (size_t pos);
//            string s = "Hello World!";  s[0] = 'h'; -> 代表可以修改
//            const char& operator[] (size_t pos) const;
//            const string s = "Hello world!";
//            std::cout << s[0] << std::endl;  -> 代表僅可以唯獨
//    7. 在一個類別的文件中，Member types的意思是指常用的一些型別別名，在文件中
//       可能會常常以一些別名來取代一些變數的原始實際型別(因為原始實際型別不好理解)
//    8. 若在文件的成員函式中，找不到建構子相關的資訊，代表該類別是使用內建的建構
//       子(預設建構子、複製建構子以及預設的列表初始化({}))進行物件的建構，如:C++的array。
//    9. 若在類別模板中看到預設子(如: template<typename Alloc = allocator<T>> 中的allocator<T>)，
//       代表該模板引數可以不用提供。
// 
// 2. Iterator迭帶器
//    * 指標是一種迭帶器，但是迭代器不一定是指標，因此，指標能做的事情迭代器也能做(如:p++)。
// 
// 3. Container容器
//    * 陣列 array                  <=>                std::array
//    * 動態陣列 dynamic array      <=>                 std::vector             Python list
//    * 單項鏈結串列 singly linked list    <=>          std::forward_list
//    * 雙向鏈結串列 doubly linked list    <=>           std::list
//    * 平衡二元搜尋樹 balanced binary search tree   <=> std::map, std::set
//    * 雜湊表 hash table     <=>     std::unordered_map, std::unordered_set    Python dict
// 
//    a. array 陣列
//       * 把同樣型態的元素在記憶體中連續擺放 => 只要知道第一個元素的位址，其他元素的位址就能計算出來。
//       * 一開始定義好大小之後就不能更改其大小，因為無法確定其附近周圍的記憶體有無被其他物件使用。
//       * a[b] <=> *(a+b)
//       * v[i] <=> *(&v[0] + i)
// 
//    b. dynamic array 動態陣列
//       * 使用指標儲存陣列配置的記憶體位址，在改變大小的時候重新配置記憶體。
//         => 對使用陣列的使用者來說，都是透過同樣的指標去拜訪陣列中的每個元素，用起來感覺沒差，
//            也就是說透過改變指標指向的位址來移動陣列，並在移動的過程中配置新的空間。
//       * size: 目前陣列已經使用到的長度
//         capacity: 目前陣列已經配置的空間
//         capacity >= size
//       * 陣列大小變更流程 (重新配置記憶體):
//         A) 使用指標儲存陣列的第一個元素記憶體位址
//         B) 配置一個更大的新空間，通常會配置兩倍大的capacity (i.e. capacity = 2*size)
//         C) 複製原有的陣列元素到新空間(新陣列)
//         D) 讓指標儲存新陣列的第一個元素記憶體位址
//         E) 釋放舊有空間，並且更新陣列的size值以及capacity值
//       * 策略: 一開始就先配置多一點空間(讓目前陣列周圍預留空間)，讓陣列大小在些微增長時
//               可以直接使用記憶體，而不是去重新配置記憶體，使得重新配置記憶體的機會降低
//    c. mapping 映射
//       * 能單向地將key(鍵)值對應到value(內容值)的資料結構
//       * 取得不存在鍵值的內容值，預設會是zero-initialized的結果
//       * std::map在儲存此種資料結構時會依照key的名字排序，
//         std::unordered_map則不會依照key的名字排序。
// 4. 在Leetcode以及工作中能用library就用library，不需要重複造車輪。
//    挑題取向：題目看得懂，看起來很簡單，但是不一定能夠做得出來的題目，一天寫一題，
//             寫不出來就看答案，了解以後背熟，背久以後就會有一些常用的工具，接著在
//             適當的時候使用這些適當的工具，隔兩天再寫一次，不停驗證，重複寫挑好的題目，
//             至少每題寫四輪，讓腦的理解能夠實踐在程式碼裡面後再去寫新題目才有意義，
//             要做到寫完的題目只要是有寫過的，即便過了半年到一年都不用再複習，一樣
//             寫得出來，不需要任何提示(也就是和高中數學一樣，題型策略，先把選擇的題
//             型弄懂背熟，再去想新的)。
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
int main() {

    /* C++中的陣列 -- array */
    std::array<int, 5> aa = {};  // 5個元素都歸零。
    aa[0] = 4;
    std::array<int, 5> bb = aa;
    std::array<int, 5> cc = {3, 4, 5, 6, 7};

    for(auto& v : aa) {  // v 相當於是*p，要注意是dereferenced(取值)完的結果。
        std::cout << v << std::endl;
    }

    // for(auto p = std::begin(aa); p != std::end(aa); p++) {  // 使用迭代器，迭代器可做加減，意思就是跳到下一個位址
    //     std::cout << *p << std::endl;
    // }

    // for(auto p = aa.begin(); p != aa.end(); p++) {  // 使用迭代器，迭代器可做加減，意思就是跳到下一個位址
    //     std::cout << *p << std::endl;
    // }

    /* C++中的動態陣列 -- vector */
    std::vector<int> va;  // default constructor
    std::vector<int> vb = {3, 9, 1, 7, 5};  // initializer list constructor
    std::cout << vb.size() << std::endl;

    vb.push_back(10);  // {3, 9, 1, 7, 5, 10}
    vb.push_back(11);  // {3, 9, 1, 7, 5, 10, 11}
    vb.pop_back();     // {3, 9, 1, 7, 5, 10}
    vb.pop_back();     // {3, 9, 1, 7, 5}

    // Use the const iterator as the first argument
    vb.insert(begin(vb), 10);  // {10, 3, 9, 1, 7, 5}
    vb.insert(end(vb), 10);  // {10, 3, 9, 1, 7, 5, 10}
    vb.erase(begin(vb)+1);  // {10, 9, 1, 7, 5, 10}
    vb.erase(end(vb)-2);  // {10, 9, 1, 7, 10}

    // begin() 或是 end() 回傳的型態是 std::vector<int>::iterator
    // 是std::vector類別裡面定義的類別，用來組織程式碼，表示API接口。

    for(int n: vb){
        std::cout << n << " ";
    }
    std::cout << std::endl;

    /* C++中的動態陣列 -- vector */
    std::map<int, int> ma;  // 小型資料庫的概念。
    ma[3] = 9;
    ma[4] = 7;
    ma[99] = 100;
    ma[-4] = 10;
    ma[-100] = 100;

    ma[4] = 9999;

    // From the documents, we know the map has following usages:
    for(auto p = std::begin(ma); p != std::end(ma); p++){
        auto v = *p;  // p為迭代器，取值後會得到std::pair<int, int>
                      // (視std::map使用的模板參數而定)的資料型態。
        std::cout << v.first << ", " << v.second << std::endl;
    }

    for(const auto& v: ma) { // 注意這邊的v相當於是上面p去dereferenced完的結果，也就是std::pair。
        std::cout << v.first << ", " << v.second << std::endl;
    }

    for(auto [k, n]: ma) { // 此為最新語法，使用時記得型態一定是auto。
        std::cout << k << ", " << n << std::endl;
    }

    std::cout << ma[3] << ", " << ma[4] << ", " << ma[99] << ", " << ma[-4] << ", " << ma[0] << std::endl;

    /* 泛型演算法 */ 
    // 指可套用在各種型態、資料結構、容器也可以
    // 透過function或是lambda自定義不一樣的運算規則(客製化行為)的演算法，
    // 如: <algorithm> 中的 std::sort()
    // count() -> 計算某個元素在容器中出現了幾次。
    // find()  -> 尋找某個元素在容器中出現的位置。
    // swap()  -> 在容器中交換元素。
    // fill()  -> 對容器中每個元素填滿特定的值。
    // random_shuffle() -> 對容器中的元素進行洗牌。
    // max_element() -> 找容器中的最大值。
    std::vector<int> vc = {3, 9, 1, 7, 5};
    std::sort(std::begin(vc), std::end(vc));
    for(int n: vc) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::cout << *std::max_element(std::begin(vc), std::end(vc)) << std::endl;

    std::string sa = "I Love Cpp.";
    std::random_shuffle(std::begin(sa), std::end(sa));
    for(auto& val: sa) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::sort(std::begin(sa), std::end(sa));
    for(auto& val: sa){
        std::cout << val << " ";
    }

    return 0;
}