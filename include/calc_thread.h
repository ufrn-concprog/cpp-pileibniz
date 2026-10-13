/**
 * @file    calc_thread.h
 * @brief   Thread task for computing a term in the Leibniz series
 * @author	Everton Cavalcante (everton.cavalcante@ufrn.br)
 * @date	  October 12, 2026
 */

#ifndef CALC_THREAD_H
#define CALC_THREAD_H

#include <barrier>
#include <vector>

using std::barrier;
using std::vector;

/**
 * @class   CalcThread
 * @brief   Computes one term of the Leibniz series and synchronizes with peers.
 * @details Each instance is intended to run in its own thread.
 *          It writes the term for its index into the corresponding element
 *          of the shared terms vector, then waits until all participating
 *          threads reach the barrier.
 */
class CalcThread {
public:
  /**
   * @brief Constructs a worker for one Leibniz-series term.
   * @param index Term index.
   * @param terms Shared output vector where the computed term will be stored.
   * @param sync_barrier Synchronization barrier shared by all worker threads.
   */
  CalcThread(int index, vector<double> &terms, barrier<> &sync_barrier);

  /**
   * @brief Computes and stores this worker's term, then waits at the barrier.
   */
  void operator()();

private:
  /** @brief Index of the term computed by this worker. */
  int index;

  /** @brief Shared vector receiving the computed terms. */
  vector<double> &terms;

  /** @brief Barrier used to synchronize the worker threads. */
  barrier<> &sync_barrier;
};

#endif
