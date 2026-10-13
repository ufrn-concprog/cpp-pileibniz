/**
 * @file    sum_aggregator.cpp
 * @brief   Implements the barrier completion action
 * @author	Everton Cavalcante (everton.cavalcante@ufrn.br)
 * @date	  October 12, 2026
 */

#include "sum_aggregator.h"

#include <iostream>
using std::cout;
using std::endl;

SumAggregator::SumAggregator(vector<double> &terms) : terms(terms) {}

void SumAggregator::operator()() {
  double sum = 0.0;
  for (double term : terms) {
    sum += term;
  }
  cout << sum << endl;
}
