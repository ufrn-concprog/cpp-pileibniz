/**
 * @file    calc_thread.h
 * @brief   Thread task for computing a term in the Leibniz series
 * @author	Everton Cavalcante (everton.cavalcante@ufrn.br)
 * @date	  October 12, 2026
 */

#ifndef CALC_THREAD_H
#define CALC_THREAD_H

#include <barrier>
using std::barrier;

#include "sum_aggregator.h"

#include <vector>
using std::vector;

/**
 * @class   CalcThread
 * @brief   Computes one term of the Leibniz series and synchronizes with peers.
 * @details Each worker writes its term at its assigned index, then waits at the
 *          shared barrier.
 */
class CalcThread {
public:
  /**
   * @brief Constructs a worker for one Leibniz-series term.
   * @param index Term index.
   * @param terms Shared output vector where the computed term will be stored.
   * @param sync_barrier Barrier shared by all worker threads.
   */
  CalcThread(int index, vector<double> &terms,
             barrier<SumAggregator> &sync_barrier);

  /**
   * @brief Computes and stores the term, then waits at the shared barrier.
   */
  void operator()();

private:
  /** @brief Index of the term computed by this worker. */
  int index;

  /** @brief Shared vector receiving the computed terms. */
  vector<double> &terms;

  /** @brief Barrier reached after this worker stores its term. */
  barrier<SumAggregator> &sync_barrier;
};

#endif
