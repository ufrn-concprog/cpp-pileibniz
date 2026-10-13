/**
 * @file    main.cpp
 * @brief   Concurrent approximation of pi using the Leibniz series
 * @author	Everton Cavalcante (everton.cavalcante@ufrn.br)
 * @date	  October 12, 2026
 */

#include <barrier>
#include <iostream>
#include <thread>
#include <vector>

#include "calc_thread.h"

using std::barrier;
using std::cin;
using std::cout;
using std::endl;
using std::thread;
using std::vector;

/**
 * @brief   Reads the requested precision and computes an approximation of pi.
 * @details Creates one worker thread per Leibniz-series term.
 *          Each worker writes its term into a distinct vector element and
 *          waits at a barrier. The main thread sums the terms after all
 *          workers have completed.
 */
int main() {
  int precision = 0;
  cout << "Enter the precision (number of terms): ";
  cin >> precision;

  vector<double> terms(precision);
  double sum = 0.0;

  barrier sync_barrier(precision);

  vector<thread> threads;
  cout << "Calculating the value of pi with " << precision << " terms..."
       << endl;

  for (int i = 0; i < precision; i++) {
    threads.emplace_back(CalcThread(i, terms, sync_barrier));
  }

  for (thread &thread : threads) {
    thread.join();
  }

  for (double term : terms) {
    sum += term;
  }
  cout << "Approximated value of pi: " << sum << endl;

  return 0;
}
