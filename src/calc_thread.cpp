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
 * @param sync_barrier Synchronization barrier shared by all worker threads.
 */
CalcThread::CalcThread(int index, vector<double> &terms, barrier<> &sync_barrier)
    : index(index), terms(terms), sync_barrier(sync_barrier) {}

/**
 * @brief   Calculates the indexed Leibniz-series term and synchronizes.
 * @details The term is 4 * (-1)^index / (2 * index + 1). It is stored at
 *          its matching index in the vector before the worker waits for the
 *          other threads.
 */
void CalcThread::operator()() {
  const double term = 4 * pow(-1, index) / (2 * index + 1);
  terms[index] = term;
  sync_barrier.arrive_and_wait();
}
