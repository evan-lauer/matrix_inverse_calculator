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
 * @brief Handles index arithmetic for 2d->1d array.
 * 
 * @param size int 
 * @param row int  2d index
 * @param col int  2d index
 * @return int     1d index
 */
int calculate_index(int size, int row, int col) { return (row * size) + col; }

/**
 * @brief Creates and returns minor matrix at (row, col)
 * 
 * @param m Matrix*
 * @return Matrix* 
 */
Matrix* get_minor_matrix(Matrix* m, int row, int col)
{
    Matrix* minor_matrix = new Matrix(m->size - 1);
    for (int i = 0; i < m->size; ++i)
    {
        if (i == row) continue; // skip row
        for (int j = 0; j < m->size; ++j)
        {
            if (j == col) continue; // skip col
            int index_1d = calculate_index(m->size, i, j);
            minor_matrix->matrix.push_back(m->matrix.at(index_1d));
        }
    }
    return minor_matrix;
}

/**
 * @brief Calculates determinant of matrix m.
 * 
 * @param m Matrix*
 * @return double 
 */
double matrix_determinant(Matrix* m)
{
    if (m->size == 2) return (m->matrix.at(0) * m->matrix.at(3)) - (m->matrix.at(1) * m->matrix.at(2));

    double determinant = 0;
    for (int i = 0; i < m->size; ++i) // Cofactor expansion along 1st row
    {
        Matrix* minor_matrix = get_minor_matrix(m, 0, i);
        double minor_matrix_determinant = matrix_determinant(minor_matrix);
        if (i % 2 == 1)
        {
            determinant += -1 * minor_matrix_determinant;
        } else
        {
            determinant += minor_matrix_determinant;
        }
    }
    return determinant;
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
    Matrix* matrix_inverse = new Matrix(m->size);
    for (int i = 0; i < m->size; ++i)
    {
        for (int j = 0; j < m->size; ++j)
        {
            double entry = matrix_determinant(get_minor_matrix(m, i, j));
            if (i + j % 2 == 1) entry *= -1;
            matrix_inverse->matrix.push_back(entry);
        }
    }
    transpose_matrix(matrix_inverse);
    return matrix_inverse;
}




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
    Matrix* m_inverse = matrix_inverse(m);
    return 0;
};