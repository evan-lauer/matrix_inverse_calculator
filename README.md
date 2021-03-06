# Matrix Inverse Calculator
By Evan Lauer

The basic code (`matrix_inverse_web.cpp`, `inverse_closed_form.cpp`, and `inverse_real_valued.cpp`) is written in C++. The web interface uses Emscripten to compile C++ to Javascript, which is then leveraged by `matrix_inverse_calculator.html` to create the web view.
## Overview
This project is an online calculator which achieves two objectives: [1] Calculate the closed-form inverse equation for a general matrix of a given size and [2] Calculate the actual inverse of a real-valued matrix.

To see the code in-action in a web calculator, visit [my blog](https://evanlauer.sites.carleton.edu/index.html) (currently under construction). This interface currently only allows for [2].

## The math
Finding the inverse of a matrix can be a useful operation in linear algebra.

### Finding the inverse of a real-valued matrix:
To achieve objective [2] requires basic arithmetic:

1) For each entry (i, j) in matrix A, find the (i, j) minor matrix, and calculate its determinant.
2) Populate a new matrix with entries representing the minor matrix determinant of the given entry.
3) Transpose the new matrix. This is the inverse.

### Finding the closed-form inverse equation of a general matrix:
To achieve objective [1] is a more computationally intense task. Closed-form equations for matrix inverses tend to be very long, and to find them by hand requires a long process of row reduction of a general matrix, with a placeholder variable for each matrix entry. For a larger matrix, (5 x 5 or greater), the equations will have 25 or more variables.

This computational effort is the fundamental reason for this calculator. I've found it hard to find closed-form equations for matrix inverses. The largest one easily available online is 4 x 4. With my calculator, you can find the equation of a matrix of any size!

To achieve this requires a more intense operation. In summary, my code recursively solves for the determinants of minor matrices. 

Once the recursion reaches a small, 2 x 2 matrix, the equation (ad - bc) is returned (this is the determinant equation for a 2 x 2 matrix). 

This formula is then altered by each higher-order stack according to the rules of minor matrix determinants, until the top level. 

Once the determinant formula for each matrix entry is found, a new matrix is populated with these entries and transposed. To find the (i, j) entry of the inverse matrix, you divide the formula in the new matrix by the determinant formula for the larger matrix. Whew.

## Goals
1. Use a better algorithm -- row reduction instead of Laplace expansion
2. Add a web interface for operation [1]---IN PROGRESS
3. Cache formulas below a certain size for operation [1].
4. Finish integration with [my personal site](https://evanlauer.sites.carleton.edu) (currently under construction).

## Recent completed changes
1. Use git version control with cPanel hosting
2. Split operations [1] and [2] into separate functions, files, and front-end interfaces for faster computing time.
3. Compile to WASM instead of JS
