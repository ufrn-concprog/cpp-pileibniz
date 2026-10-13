/**
 * @file    main.cpp
 * @brief   Concurrent approximation of pi using the Leibniz series
 * @author	Everton Cavalcante (everton.cavalcante@ufrn.br)
 * @date	  October 12, 2026
 */

#include <barrier>
using std::barrier;

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::milli;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <thread>
using std::thread;

#include <vector>
using std::vector;

#include "calc_thread.h"
#include "sum_aggregator.h"

/**
 * @brief   Reads the requested precision and computes an approximation of pi.
 * @details Creates one worker thread per Leibniz-series term. When all workers
 *          reach the barrier, its completion action sums and prints the terms.
 * @return Exit status code.
 */
int main() {
  int precision = 0;
  cout << "Enter the precision (number of terms): ";
  cin >> precision;

  vector<double> terms(precision);
  barrier sync_barrier(precision, SumAggregator(terms));

  auto start = high_resolution_clock::now();

  vector<thread> threads;
  cout << "Calculating the value of pi with " << precision << " terms..."
       << endl;

  for (int i = 0; i < precision; i++) {
    threads.emplace_back(CalcThread(i, terms, sync_barrier));
  }

  for (thread &thread : threads) {
    thread.join();
  }

  auto end = high_resolution_clock::now();
  double elapsed_milliseconds = duration<double, milli>(end - start).count();
  cout << elapsed_milliseconds << " milliseconds" << endl;

  return 0;
}
