#include <barrier>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

class CalcThread {
private:
  int i;
  std::vector<double> &terms;
  std::barrier<> &_barrier;

public:
  CalcThread(int i, std::vector<double> &terms, std::barrier<> &barrier)
      : i(i), terms(terms), _barrier(barrier) {}

  void operator()() {
    double term = 4 * pow(-1, i) / (2 * i + 1);
    terms[i] = term;
    _barrier.arrive_and_wait(); // Wait for all threads to compute
  }
};

int main() {
  int precision = 0;
  std::cout << "Enter the precision (number of terms): ";
  std::cin >> precision;

  std::vector<double> terms(precision);
  std::barrier<> _barrier(precision);

  std::vector<std::thread> threads;
  std::cout << "Calculating the value of pi with " << precision << " terms..."
            << std::endl;

  for (int i = 0; i < precision; i++) {
    threads.emplace_back(CalcThread(i, terms, _barrier));
  }

  for (auto &t : threads) {
    t.join();
  }

  double sum = 0.0;
  for (int i = 0; i < terms.size(); i++) {
    sum += terms[i];
  }
  std::cout << "Approximated value of pi: " << sum << std::endl;

  return 0;
}
