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

    Matrix(int _size, vector<double> _matrix)
    {
        matrix = _matrix;
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
 * @brief Gets the value at (row, col).
 * 
 * @param m Matrix*
 * @param row int
 * @param col int
 * @return double 
 */
double matrix_get(Matrix* m, int row, int col) { return m->matrix.at(calculate_index(m->size, row, col)); }

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
        double entry = matrix_get(m,0,i);
        if (i % 2 == 1)
        {
            determinant += (-1 * minor_matrix_determinant) * entry;
        } else
        {
            determinant += (minor_matrix_determinant) * entry;
        }
        delete minor_matrix;
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
    for (int i = 0; i < m->size; ++i)
    {
        for (int j = i; j < m->size; ++j)
        {
            int index_1d = calculate_index(m->size,i,j);
            int index_1d_swap = calculate_index(m->size,j,i);
            double val = matrix_get(m, i, j);
            double val_swap = matrix_get(m, j, i);
            m->matrix[index_1d] = val_swap;
            m->matrix[index_1d_swap] = val;
        }
    }
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
    double det = matrix_determinant(m);
    for (int i = 0; i < m->size; ++i)
    {
        for (int j = 0; j < m->size; ++j)
        {
            double entry = matrix_determinant(get_minor_matrix(m, i, j));
            if (i + j % 2 == 1) entry *= -1;
            matrix_inverse->matrix.push_back(entry/det);
        }
    }
    transpose_matrix(matrix_inverse);
    return matrix_inverse;
}






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


/**
 * @brief Returns the given matrix as an encoded string for wasm/JS interaction.
 * 
 * @example (1,2,3),(4,5,6),(7,7,7) is encoded as "1,2,3,\n,4,5,6,\n,7,7,7,\n,"
 * 
 * @param m 
 * @return const char* 
 */
const char* export_matrix_as_string(Matrix* m)
{
    string str = "";
    for (int i = 0; i < m->size; ++i)
    {
        for (int j = 0; j < m->size; ++j)
        {
            str += to_string(matrix_get(m, i, j)) + ",";
        }
        str += "\n,";
    }
    delete m;
    return str.c_str();
}



Matrix* decode_input_string(const char* matrix_str) // this method is messy. improve soon
{
    char delimiter = ',';

    string token = "";

    int dimension_counter = 0;

    vector<double> matrix_as_doubles = {};
    for ( ; *matrix_str != '\0'; matrix_str++) // iterate through const char*
    {
        if (*matrix_str == delimiter) // if delimiter found, convert token to double, push into double vector, reset token
        {
            if (token.size() == 0) // skip empty tokens (newlines)
            {
                continue;
            }
            double matrix_entry = stod(token);
            matrix_as_doubles.push_back(matrix_entry);
            token = "";
        } else
        if (*matrix_str == '\n') // if newline found, increment the dimension (tricky little algorithm to find the matrix size)
        {
            dimension_counter++;
            continue;
        } else                   // if neither newline nor delimiter, add char to the token.
        {
            token = token + *matrix_str;
        }
    }
    return new Matrix(dimension_counter, matrix_as_doubles);
}

extern "C"
{
    const char* matrix_inverse_JS_interact(const char* matrix_str)
    {
        Matrix* matrix = decode_input_string(matrix_str);
        Matrix* inverse = matrix_inverse(matrix);
        delete matrix;
        return export_matrix_as_string(inverse);
    }
}

int main()
{
    const char* matrix_str = "1,2,3.5,\n,2.5,-1,0,\n,0,0,-1.3,\n,";
    Matrix* matrix_m = matrix_inverse(decode_input_string(matrix_str));
    return 1;
}

