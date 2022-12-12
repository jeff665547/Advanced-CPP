// 物件導向程式設計
// 目的：
//     * 將程式碼責任釐清(讓事情變得簡單、清楚)，並使軟體可以規模化。
//     * 著重在類別之間使用(使用者層面，怎麼使用它)上的關係(不是在邏輯上、物理上、化學上、數學上的關係)。
//       也就是說不同類別的某個函式執行行為的預期結果可能是一樣的 => 可以異中求同、同中存異。
//       管理好此種關係以達到一個好的設計(以方便使用為目的)。
// 應用範圍：
//     1. 與他人協作的管理問題。
//     2. 在不影響程式其他正常功能的前提下進行軟體更新或是新增功能。
//     3. 寫庫(library)提供給別人使用時的界線(面)。
// 
// 
// * (衍生類別的)物件透過繼承發生的隱性轉型不會產生新的物件，而是在該物件中取得基底類別部分的子物件。
// * virtual 回傳值 成員函式 => 代表請C++幫忙查看呼叫成員函式的物件本身是否只是單純的基底類別實例，
//    (又被稱做虛擬函式)        還是其實是某個衍生類別物件or某個衍生類別物件中的一部份(i.e. 基底類
//                             別部分的子物件(透過參考或指標))，
//                             如果是前者(基底類別實例)的話，就會直接去呼叫基底類別的成員函式。
//                             如果是後者的話(某個衍生類別物件or某個衍生類別物件中的一部份)，就會
//                             先去查看衍生類別內是否有同名成員函式，如果有的話，
//                             就會去呼叫該同名的成員函式，如果沒有的話就會去呼叫基底類別的成員函式。
// * virtual 回傳值 成員函式 = 0; => 將虛擬函式指定為0就會成為抽象函式，抽象函式不能也不需要定義。
//    (又被稱作抽象(abstract)函式    所有的衍生類別都要去定義抽象函式的實作，否則該衍生類別也會
//     、介面、合約)                 變成抽象類別，無法建構物件。
// 
// * 具有抽象函式的類別稱為抽象類別，不能直接建構物件，因為在該類別中有不能定義的抽象成員函式，
//   要每個成員函式都有定義才能建構物件。
// * 抽象類別物件無法單獨存在(因其無法建構)，其必須要依附(參考)某個繼承此抽象類別的衍生類別物件。
// * 使用virtual會需要額外付出一些成本(因為它所在的類別也是需要實例化)，會影響效率。
// * 物件導向中的繼承是動態(執行期)多型(讓不同的類別當成同一個類別使用)，泛型則是靜態(編譯期)多型。
#include <iostream>
#include <vector>
class IShape{                     // * 若一個類別中只單純擁有抽象函式的話(如:IShape)，
                                  //   則其又被稱為Interface(介面)。其所傳達的資訊
                                  //   (以Shap為例)為，身為一個Shape的衍生類別需要提
                                  //   供(定義)那些功能。
  public:
    virtual void Draw() const = 0;
    virtual void Color() const = 0;
    virtual void Area() const = 0;
};

class Shape{                       // * 新增一個類別來表達不同形狀間的共通點
  public:
    Shape() = default;
    Shape(int x, int y) : x(x), y(y) {};
    virtual void Draw() const {return;}  // * 加了virtual以後才能被衍生類別的同名函式所覆蓋(override)。
    // virtual void Color() const = 0;   // * 抽象(成員)函式會強迫其衍生類別去定義與此同名的成員函式，
                                         //   如果沒有定義，該衍生類別也會變成抽象類別，和此基底類別一樣，
                                         //   無法產生物件。
    virtual void Color() const {return;}
    virtual double Area() const {        
        return 0;
    }
  protected:                       // * protected權限管制：設定為protected，除了同一個類別內的
                                   //   成員函式可以存取外，衍生類別的成員函式也可以存取，但是其
                                   //   他地方則不能存取。
                                   // * 然而如果是private的話，就只有同一個類別的成員函式才可以
                                   //   存取，衍生類別的成員函式則不能存取。
    double x, y;                   // * 將衍生類別間共有的部分定義在基底類別中，避免重複撰寫。
};

class Rectangle : public Shape {   // Rectangle (衍生類別) 去繼承 Shape (基底類別) 
                                   // (i.e. 繼承圖形方向為 Rectangle -> Shape)
                                   // * 透過繼承，Rectangle類型的物件可以隱性轉型成Shape類型的物件，
  public:                          //   反之則不行。因為每個衍生類別物件都會包含一個基底類別物件，在
                                   //   衍生類別物件產生時就會順便在該衍生類別物件內產生(沒有名字的)
                                   //   基底類別物件。
    Rectangle(double x, double y, double w, double h) :
        width(w), height(h)
    {
        this->x = x;    // * x 以及 y 為 Shape 類別的資料成員，無法直接在Rectangle類別底下拿取 x 或是 y。
                        //   解法一：this的隱性轉型(不需要透過基底類別的建構子)
                        //   必須要先拿到Shape類別的物件才能拿到 x 以及 y ，這邊的this為衍生類別
                        //   (Rectangle)物件的指標，可以隱性轉型成基底類別(Shape)物件的指標來存取基底類
                        //   別成員。除此之外，如果此處Shape的資料成員名稱與建構子中的參數名稱不相同，
                        //   則this可以進一步地省略。
        this->y = y;
    }
    void Draw() const {
        std::cout << "[Rectangle] " 
                  << "x: " << x << ", "          // * 這裡省略了this(基底類別物件的指標(經衍生類別的
                                                 //   隱性轉型))，因為此處沒有撞名問題。
                  << "y: " << y << ", "
                  << "width: " << width << ", "
                  << "height: " << height << std::endl;
    }
    void Color() const {
        std::cout << "Blue" << std::endl;
    }
    double Area() const {
        return width * height;
    }
    double width, height;
};

class Circle : public Shape{
  public:
    Circle(double x, double y, double radius) :
        Shape(x, y), radius(radius)
    {
        // * x 以及 y 為 Shape 類別的資料成員，無法直接在Rectangle類別底下拿取 x 或是 y。
        //   解法二：使用基底類別(Shape)的建構子
        //   在衍生類別(Circle)的建構子裡可以呼叫基底類別(Shape)的建構子來初始化基底類別(Shape)的成員。
    }
    void Draw() const {
        std::cout << "[Circle] " 
                  << "x: " << x << ", "
                  << "y: " << y << ", "
                  << "radius: " << radius << std::endl;
    }
    void Color() const {
        std::cout << "Pink" << std::endl;
    }
    double radius;
};

int main() {
    const Rectangle r{2.0, 3.0, 2.4, 4.5};
    const Circle c{3.0, 4.5, 2.2};

    // Goal: 因為對r和c具有相同的期待(都有Draw函式，並且都是希望去畫出一些東西)
    //       因此希望能將兩個不同類型的物件一起放到同一個vector裡，希望一起在同
    //       一層迴圈中去執行Draw函式。 
    //       => * 產生新的類別(基底類別)讓這兩個類別去繼承，
    //            將對兩個類別中共同期待的部分放進一個新的類別(而不是去修改原本已經存在的東西)。
    // * 使用繼承好處：衍生類別(derived)可以隱性轉型成基底類別(base)。
    std::vector<Shape> shapes = {r, c};       // * 此種寫法代表，r和c都會隱性轉型成基底類別的物件
                                              //   並且將該轉型後的物件內容複製到陣列裡，在陣列裡
                                              //   的元素失去了衍生類別物件的內容。
    std::vector<const Shape*> sa = {&r, &c};  // * 這裡使用const Shape*的原因是因為r和c都是唯讀的
                                              //   且(無論是動態還是靜態)陣列的元素類型不能是參考，
                                              //   再加上為了讓sa內的元素能夠使用各自衍生類別的
                                              //   Draw()，因此只能讓sa內的元素使用指標去指向
                                              //   r以及c物件內部基底類別部分的子物件。
    for(const Shape* ele: sa){
        ele->Draw();
    }

    Shape s = r;  // * r會隱性轉型成Shape類型的物件(在r裡面基底類別部分的子物件)，
                  //   接著再呼叫Shape的複製建構子來建構s物件，也就是說
                  //   s是r裡Shape類別子物件的複製品。
    s.Draw();     // * 此處呼叫的Draw為Shape的Draw，並非Rectangle的Draw。
    r.Draw();     // * 此處呼叫的Draw為Rectangle的Draw，並非Shape的Draw。
    s.Area();     // * 此處呼叫的Area為Rectangle的Area，並非Shape的Area。
                  //   (因為衍生類別Rectangle有定義Area成員函式。)

    c.Draw();     // * 此處呼叫的Draw為Circle的Draw，並非Shape的Draw。
    c.Area();     // * 此處呼叫的Area為Shape的Area，並非Circle的Area。
                  //   (因為衍生類別Circle沒有Area成員函式，所以c會先
                  //    隱性轉型成基底類別Shape再去呼叫Area成員函式)。

    const Shape& ss = r; // * r會隱性轉型成Shape類型的物件(在r裡面基底類別部分的子物件)，
                         //  接著ss去參考(引用)隱性轉型出來的暫時物件，也就是說，ss只代表
                         //  r裡面的其中一部分(屬於基底類別Shape的那一部分)。
    ss.Draw();           // * 此處的Draw依舊為Shape的Draw。
    ss.Color();          // * 此處的Color為Rectangle的Color，因為Shape的Color為virtual的，
                         //   又因ss實際上為r中的一部份，然後衍生類別Rectangle也有定義Color。
                         //   所以會去呼叫衍生類別的Color。

    for(const Shape* ele: sa){
        std::cout << ele->Area() << std::endl;  // 如果基底類別的Area不是virtual，則這邊使用
                                                // 的Area全部都是基底類別(Shape)的Area函式,
                                                // 因為sa的元素每一個都是基底類別的指標，再加上
                                                // 沒有virtual來幫忙判定，因此一律使用基底類
                                                // 別的Area函式
    }

    return 0;
}