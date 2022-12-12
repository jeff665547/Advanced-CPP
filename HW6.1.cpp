#include <iostream>
#include <string>

class MyCout{
  public:
    MyCout& operator<<(const char* val) {
        printf("%s", val);
        return *this;
    }
    MyCout& operator<<(const char& val) {
        printf("%c", val);
        return *this;
    }
    MyCout& operator<<(const int& val) {
        printf("%d", val);
        return *this;
    }
    MyCout& operator<<(const double& val) {
        printf("%f", val);
        return *this;
    }
};

MyCout myCout;
char myEndl = '\n';

int main(){
    myCout << "3 + 5 == " << 3 + 5 << myEndl
           << "3 / 5 == " << 3 / 5. << myEndl;

    return 0;
}