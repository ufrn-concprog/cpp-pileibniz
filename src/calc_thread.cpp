/**
 * @file    calc_thread.cpp
 * @brief   Implementation of the Leibniz-series thread task
 * @author	Everton Cavalcante (everton.cavalcante@ufrn.br)
 * @date	  October 12, 2026
 */

#include "calc_thread.h"

#include <cmath>
using std::pow;

/**
 * @brief Constructs a worker for one Leibniz-series term.
 * @param index Term index.
 * @param terms Shared output vector where the computed term will be stored.
 * @param sync_barrier Barrier shared by all worker threads.
 */
CalcThread::CalcThread(int index, vector<double> &terms,
                       barrier<SumAggregator> &sync_barrier)
    : index(index), terms(terms), sync_barrier(sync_barrier) {}

/**
 * @brief Calculates and stores this worker's Leibniz-series term.
 * @details The term is 4 * (-1)^index / (2 * index + 1). It is stored at
 *          its matching index in the shared vector before the worker waits at
 *          the barrier.
 */
void CalcThread::operator()() {
  const double term = 4 * pow(-1, index) / (2 * index + 1);
  terms.push_back(term);
  sync_barrier.arrive_and_wait();
}
