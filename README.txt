HW 2: Floating-Point Overflow Handler

The utility will check whether the value of the loop increment overflows and loses its precision based on a certain bound of the loop. It will find the minimum threshold value at which the increment value is "lost" due to the 24-bit significand limitation.

Requirements:
A C++ compiler (e.g., g++)

Standard C++11 or higher

Build Instructions

In order to run this program, you can use the following command in your terminal:

g++ -std=c++11 fp_overflow_checker.cpp -o fp_overflow_checker


Running the Program

The program expects two arguments, loop bound and increment value.

./fp_overflow_checker <bound> <increment>


Example:

./fp_overflow_checker 1e8 1.0


Known Bugs & Limitations:

It assumes positive input values as per assignment specifications.

It doesn't handle NaN and Subnormal input values.

The threshold calculation assumes a simple addition-based loop counter.