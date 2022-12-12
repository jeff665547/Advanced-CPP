#include <iostream>
#include <string>

// template<typename T>
// void Print(T input){
//     std::cout << input;
// }

void Print(std::string input){
    std::cout << input;
}

void Print(int input){  // 如果沒有定義此版本的函數，int會直接隱性轉型成字元(char)，接著再使用char版本的函數
                        // 轉成字元以後用ASCII code印出來，不是什麼字元都可以被印出來，
                        // 例如：4這個字元代表傳輸結束，8這個字元則代表退格。
    std::cout << input;
}

void Print(double input){  // 如果沒有定義
    std::cout << input;
}

void Print(char input){
    std::cout << input;
}

int main() {

    Print("Hello");
    Print("\n");
    Print(4);
    Print('\n');
    Print(8.7);

    return 0;
}