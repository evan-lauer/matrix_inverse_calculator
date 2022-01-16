#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Defines a matrix using double[]. Represents a 2d matrix with 1d array
 * using index arithmetic.
 * 
 */
class Matrix
{
    public:
    int size;
    vector<double> matrix;

    Matrix(int _size)
    {
        size = _size;
    }
};

/**
 * @brief Handles index arithmetic for 2d->1d array.
 * 
 * @param size int 
 * @param row int  2d index
 * @param col int  2d index
 * @return int     1d index
 */
int calculate_index(int size, int row, int col) { return (row * size) + col; }


/**
 * @brief Sets the value at (row, col) to val.
 * 
 * @param m Matrix*
 * @param row int
 * @param col int
 * @param val double
 */
/*
void matrix_set(Matrix* m, int row, int col, double val)
{
}
*/


/**
 * @brief Gets the value at (row, col).
 * 
 * @param m Matrix*
 * @param row int
 * @param col int
 * @return double 
 */
double matrix_get(Matrix* m, int row, int col) { return m->matrix.at(calculate_index(m->size, row, col)); }


/**
 * @brief Implements CLI for easy testing (as opposed to hard-coding 2d vectors.)
 * 
 * @return Matrix*
 */
Matrix* populate_matrix()
{
    cout<< "Square matrix dimension (should be integer > 2): ";
    int dimension;
    cin>> dimension;
    if (dimension < 3) { cerr<< "Dimension should be integer > 2."; exit(-1); }
    

}

int main()
{
    return 0;
};