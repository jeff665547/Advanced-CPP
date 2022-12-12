#include <iostream>

class Grade{
public:
  bool operator>=(int other) const {
    return val >= other;
  }
  bool operator<(int other) const {
    return val < other;
  }
  int val;
};

std::ostream& operator<<(std::ostream& os, const Grade& g) {
  os << g.val;
  return os;
}

int main() {
  const Grade gs[5] = { 80, 60, 59, 90, 40};
  
  std::cout << "PASS: ";
  for (const auto& g : gs) {
    if (g >= 60) {
      std::cout << " " << g;
    }
  }
  std::cout << std::endl;
  
  std::cout << "FAIL: ";
  for (const auto& g : gs) {
    if (g < 60) {
      std::cout << " " << g;
    }
  }
  std::cout << std::endl;
  return 0;
}