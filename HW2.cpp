#include <iostream>
#include <string>

void SplitInteger(const int& input) {
    std::string str = std::to_string(input);
    for(int i = 0; i < str.size(); i++){
        std::cout << str[str.size()-i-1] << " ";
    }
    std::cout << std::endl;

    int tmp = input;
    while(tmp/10 || tmp%10){
        std::cout << tmp%10 << " ";
        tmp /= 10;
    }
    std::cout << std::endl;
}

int main(){
    SplitInteger(1234);
    SplitInteger(567890);
    return 0;
}