/**
 * @file    calc_thread.cpp
 * @brief   Implementation of the Leibniz-series thread task
 */

#include "calc_thread.h"

#include <cmath>

CalcThread::CalcThread(int index, std::vector<double> &terms,
                       std::barrier<> &barrier)
    : index(index), terms(terms), barrier(barrier) {}

void CalcThread::operator()() {
  const double term = 4 * std::pow(-1, index) / (2 * index + 1);
  terms[index] = term;
  barrier.arrive_and_wait();
}
