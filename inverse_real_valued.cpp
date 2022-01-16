#include <vector>
#include <iostream>
#include <string>

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
 * @brief Calculates determinant of matrix m.
 * 
 * @param m Matrix*
 * @return double 
 */
double matrix_determinant(Matrix* m)
{

}

/**
 * @brief Transposes matrix m
 * 
 * @param m Matrix*
 */
void transpose_matrix(Matrix* m)
{

}

/**
 * @brief Calculates the inverse of matrix m. Returns as new matrix.
 * 
 * @param m Matrix*
 * @return Matrix* 
 */
Matrix* matrix_inverse(Matrix* m)
{

}



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
    Matrix* m = new Matrix(dimension);
    if (dimension < 3) { cerr<< "Dimension should be integer > 2."; exit(-1); }
    for (int i = 0; i < dimension; i++)
    {
        cout<<"\nRow " + to_string(i+1) + ":\n";
        for (int j = 0; j < dimension; j++)
        {
            cout<<"Entry A " + to_string(i + 1) + to_string(j + 1) + ": ";
            double entry;
            cin>>entry;
            m->matrix.push_back(entry);
        }
    }
    return m;
}

int main()
{
    Matrix* m = populate_matrix();
    return 0;
};