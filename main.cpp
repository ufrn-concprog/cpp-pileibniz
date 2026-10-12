/**
 * @file    main.cpp
 * @brief   Concurrent approximation of pi using the Leibniz series
 */

#include <barrier>
#include <iostream>
#include <thread>
#include <vector>

#include "calc_thread.h"

int main() {
  int precision = 0;
  std::cout << "Enter the precision (number of terms): ";
  std::cin >> precision;

  std::vector<double> terms(precision);
  double sum = 0.0;

  std::barrier barrier(precision);

  std::vector<std::thread> threads;
  std::cout << "Calculating the value of pi with " << precision << " terms..."
            << std::endl;

  for (int i = 0; i < precision; i++) {
    threads.emplace_back(CalcThread(i, terms, barrier));
  }

  for (std::thread &thread : threads) {
    thread.join();
  }

  for (double term : terms) {
    sum += term;
  }
  std::cout << "Approximated value of pi: " << sum << std::endl;

  return 0;
}
