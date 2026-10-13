# Concurrent Calculation of the Leibniz Series using Barriers in C++

![C++](https://img.shields.io/badge/C++-20%2B-green?logo=c++)
![Build](https://img.shields.io/badge/build-manual-lightgrey)
[![Docs](https://img.shields.io/badge/doc-Doxygen-purple)](./doc/index.html)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

This project implements a concurrent solution in the C++ programming language to calculate an approximation of $\pi$ using the [Leibniz infinite series](https://en.wikipedia.org/wiki/Leibniz_formula_for_pi):

$$\pi = 4 \sum_{i=0}^{\infty} \frac{(-1)^i}{2i + 1} = 4 \left( 1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9} - \dots \right)$$

This repository serves a pedagogical purpose, demonstrating how to coordinate multiple concurrently running threads using a barrier as a synchronization mechanism with C++'s [`barrier`](https://en.cppreference.com/cpp/thread/barrier) object.

## 📃 About

A **barrier** is a synchronization mechanism that causes multiple threads to wait at a designated synchronization point until a specified number of threads have arrived.

### Execution Workflow

1. **Decomposition and thread spawning**: The user inputs the number of terms (`precision`) when prompted by the program. An independent worker thread ([`CalcThread`](include/calc_thread.h)) is spawned for each term $i \in [0, \text{precision}-1]$.
2. **Partial term calculation**: Each thread computes its $i$-th term:

   $$term_i = 4 \cdot \frac{(-1)^i}{2i + 1}$$

3. **Shared storage**: The computed partial term is appended to a shared vector.
4. **Waiting at the barrier**: After appending its value, each [`CalcThread`](include/calc_thread.h) calls [`arrive_and_wait()`](https://en.cppreference.com/cpp/thread/barrier/arrive_and_wait), suspending execution until all other worker threads finish their computations.
5. **Barrier action execution**: When the last thread calls `arrive_and_wait()`, the barrier automatically triggers a [`SumAggregator`](include/sum_aggregator.h) completion function before releasing the threads.
6. **Result aggregation**: [`SumAggregator`](include/sum_aggregator.h) sums all partial values stored in the list and outputs the computed approximation of $\pi$.

## 📂 Repository Structure

```text
cpp-pileibniz/
├── doc/                        # Generated Doxygen HTML documentation
├── include/                    # Header files
    ├── calc_thread.h           # Thread task for computing a term
    ├── sum_aggregator.h        # Barrier completion action that sums terms
├── main.cpp                    # Main entry point
├── README.md
└── src/
    ├── calc_thread.cpp         # Implementation of the thread task
    └── sum_aggregator.cpp      # Implementation of the barrier completion action
```

## 🚀 Getting Started

### Prerequisites

* A C++ compiler with C++20 support, such as GCC or Clang
* A terminal or IDE
* GNU Make for the Makefile targets
* [Doxygen](https://www.doxygen.nl), only if you want to generate the HTML documentation

The Makefile uses the `CXX` environment variable to select the compiler and defaults to `c++`. To use a specific compiler, set `CXX` when invoking `make`, for example `make CXX=g++-15`.

### Compilation

Inside the project root, compile all sources from the [Makefile](Makefile):

```bash
make
```

This creates the compiled object files in the `build/` directory and the `pileibniz` executable in the `bin` directory.

### ▶️ Running

Run the program and enter the number of terms when prompted:

```bash
./bin/pileibniz
```

Example of output:

```text
Enter the precision (number of terms): 4000
Calculating the value of pi with 4000 terms...
3.14307
40.5067 milliseconds
```

## ⚠️ Caveat

The computation of the approximation to $\pi$ with a large number of terms (threads) is likely to make the program fail due to excessive thread creation.
