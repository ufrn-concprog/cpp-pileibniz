#include <barrier>
#include <iostream>
#include <vector>

class CalcThread {
private:
  int i;
  std::vector<double> terms;
  std::barrier<> _barrier;

public:
  CalcThread(int i, std::vector<double> terms, std::barrier<> barrier)
      : i(i), terms(terms), _barrier(barrier) {}

  void operator()() { std::cout << message << endl; }
};

int main() {
  std::cout << "Hello World" << std::endl;
  return 0;
}
