/**
 * @file    sum_aggregator.h
 * @brief   Barrier completion action that sums Leibniz-series terms
 * @author	Everton Cavalcante (everton.cavalcante@ufrn.br)
 * @date	  October 12, 2026
 */

#ifndef SUM_AGGREGATOR_H
#define SUM_AGGREGATOR_H

#include <vector>
using std::vector;

/**
 * @class SumAggregator
 * @brief Sums and prints the terms when all worker threads reach the barrier.
 */
class SumAggregator {
public:
  /**
   * @brief Creates the completion action for a shared term vector.
   * @param terms Vector containing the computed series terms.
   */
  SumAggregator(vector<double> &terms);

  /**
   * @brief Computes and prints the sum of all terms.
   */
  void operator()();

private:
  /** @brief Shared vector containing the computed series terms. */
  vector<double> &terms;
};

#endif
