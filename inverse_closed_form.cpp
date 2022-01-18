#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Matrix
{
    public:
    int size;
    vector<string> matrix;

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
 * @brief Returns the string at (row,col)
 * 
 * @param m Matrix*
 * @param row int
 * @param col int
 * @return string 
 */
string matrix_get(Matrix* m, int row, int col) { return m->matrix.at(calculate_index(m->size, row, col)); }

/**
 * @brief Gets the minor matrix  at (row, col).
 * 
 * @param m Matrix*
 * @param row int
 * @param col int
 * @return Matrix* Minor matrix
 */
Matrix* get_minor_matrix(Matrix* m, int row, int col)
{
    Matrix* minor_matrix = new Matrix(m->size - 1);
    for (int i = 0; i < m->size; ++i)
    {
        if (i == row) continue;
        for (int j = 0; j < m->size; ++j)
        {
            if (j == col) continue;
            minor_matrix->matrix.push_back(m->matrix.at(calculate_index(m->size,i,j)));
        }
    }
    return minor_matrix;
}

/**
 * @brief Transposes the given matrix.
 * 
 * @param m Matrix*
 */
void transpose_matrix(Matrix* m)
{
    for (int i = 0; i < m->size; ++i)
    {
        for (int j = i; j < m->size; ++j)
        {
            int index_1d = calculate_index(m->size,i,j);
            int index_1d_swap = calculate_index(m->size,j,i);
            string val = matrix_get(m, i, j);
            string val_swap = matrix_get(m, j, i);
            m->matrix[index_1d] = val_swap;
            m->matrix[index_1d_swap] = val;
        }
    }
}

/**
 * @brief Returns the closed-form determinant equation for the given 2x2 matrix.
 * 
 * @param m Matrix*
 * @return string Closed-form equation
 */
string matrix_determinant_closed_form_2x2(Matrix* m)
{
    return "(" + m->matrix.at(0) + "*" + m->matrix.at(3) + " - " + m->matrix.at(1) + "*" + m->matrix.at(2) + ")";
}

/**
 * @brief Returns a string representing the closed-form equation for the determinant
 * of the given matrix.
 * 
 * @param m Matrix* 
 * @return string Closed-form equation
 */
string matrix_determinant_closed_form(Matrix* m)
{
    if (m->size == 2) return matrix_determinant_closed_form_2x2(m);
    string ret = "(";
    for (int i = 0; i < m->size; ++i)
    {
        if (i % 2 == 1)
        {
            ret += " - (" + matrix_get(m, 0, i) + ")"; // concatenates (-a11), for example
        } else
        {
            if (i != 0) ret += " + "; // concatenates plus sign if needed
            ret += "(" + matrix_get(m, 0, i) + ")"; // concatenates (a11), for example
        }
        Matrix* minor_matrix = get_minor_matrix(m, 0, i);
        ret += matrix_determinant_closed_form(minor_matrix);
    }
    return ret + ")";
}

/**
 * @brief Populates a matrix of given size with placeholder values formatted as "aIJ", where
 * I is the row number and J is the column number.
 * 
 * @param size 
 * @return Matrix* 
 */
Matrix* populate_matrix(int size)
{
    Matrix* m = new Matrix(size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            m->matrix.push_back("a" + to_string(i+1) + to_string(j+1));
        }
    }
    return m;
}

void pretty_print_matrix(Matrix* m)
{
    for (int i = 0; i < m->size; ++i)
    {
        for (int j = 0; j < m->size; ++j)
        {
            cout << matrix_get(m, i, j) + "   ";
        }
        cout << endl;
    }
}

/**
 * @brief Returns a Matrix containing closed-form equations for each entry of the
 * inverse. Each equation must be divided by the determinant to get the proper entry.
 * 
 * @param dimension int  Dimension of a square matrix
 * @return Matrix*       Strings representing closed-form inverse equations
 */
Matrix* matrix_inverse_closed_form(int size)
{
    Matrix* matrix = populate_matrix(size);
    Matrix* matrix_inverse_closed_form = new Matrix(size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            Matrix* minor_matrix = get_minor_matrix(matrix, i, j);
            matrix_inverse_closed_form->matrix.push_back(matrix_determinant_closed_form(minor_matrix));
        }
    }
    return matrix_inverse_closed_form;
}

int main()
{
    Matrix* inverse_closed_form = matrix_inverse_closed_form(3);
    pretty_print_matrix(inverse_closed_form);
    return 1;
}

extern "C"
{

const char* export_as_str(Matrix* m)
{
    string str = "";
    for (int i = 0; i < m->size; ++i)
    {
        for (int j = 0; j < m->size; ++j)
        {
            str += matrix_get(m, i, j) + ",";
        }
        str += "\n,";
    }
    return str.c_str();
}

}
