# Fibonacci Flexer

Ultra-fast Fibonacci number calculator supporting arbitrarily large numbers.

## Features

- Calculate Fibonacci numbers up to F(10,000,000)
- Arbitrary precision using GMP library
- Memory-efficient caching system
- Sub-second computation for most inputs

## Requirements

- GCC compiler
- GMP (GNU Multiple Precision Arithmetic) library
- Linux environment

## Installation

You'll need libgmp-dev

git clone https://github.com/alexcu2718/fibonacci_flex.git

cd fibonacci_flexer

gcc -O3 fib.c -lgmp -o fib

## Usage

./fib 100 # shows time taken to calculate

./fib 100 -p # prints result to console, note, this WILL flood console for high numbers
