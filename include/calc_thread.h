/**
 * @file    calc_thread.h
 * @brief   Thread task for computing a term in the Leibniz series
 */

#ifndef CALC_THREAD_H
#define CALC_THREAD_H

#include <barrier>
#include <vector>

/**
 * @brief Computes one term of the Leibniz series and synchronizes with peers
 */
class CalcThread {
public:
  CalcThread(int index, std::vector<double> &terms, std::barrier<> &barrier);

  void operator()();

private:
  int index;
  std::vector<double> &terms;
  std::barrier<> &barrier;
};

#endif
