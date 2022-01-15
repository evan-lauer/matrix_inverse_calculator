/*
This code calculates the inverse of a matrix.

This code has two functions. 1) Calculate the inverse of an actual matrix, and
2) Calculate the *formula* for the inverse of a matrix of a given size.

Finding the formula for the inverse of a matrix is a computationally intense task. To find
this formula, conduct the following operations:

1) For each entry in the matrix, do the following:
 a) Calculate the formula for the determinant of the minor matrix at the given entry.
    This formula is found through a recursive function, determinant().
2) Populate a new matrix using the formulas found in step 1a). 
3) Find the transpose of the new matrix.

In this code, a matrix is represented as a vector<vector<tuple>>, where each entry
can store both a string and an integer value. 

Because of this data structure, the code is able to return a closed-form equation for
the inverse of a matrix of any given size, as well as the actual inverse of a real matrix.

As a result, this code is not optimized for calculating real inverses--it is better suited for
calculating closed-form equations. 

Author: Evan Lauer

*/

#include <vector>
#include <iostream>
#include <sstream>
#include <tuple>

using namespace std;

// Returns a string representation of the (row, col) entry of a matrix.
//
string* get_entry_name(int row, int col)
{
    return new string("a" + std::to_string(row + 1) + std::to_string(col + 1));
}

// Transposes the given matrix.
//
vector<vector<tuple<string*, double>>*>* transpose(vector<vector<tuple<string*, double>>*>* matrix)
{
    vector<vector<tuple<string*, double>>*>* new_matrix = new vector<vector<tuple<string*, double>>*>();
    for (int col = 0; col < matrix->size(); col++) // traverses by column, appends by row, thus getting the transpose
    {
        vector<tuple<string*, double>>* new_row = new vector<tuple<string*, double>>();
        for (int row = 0; row < matrix->size(); row++)
        {
            new_row->push_back(matrix->at(row)->at(col)); // appends the (row, col) value to the new row
        }
        new_matrix->push_back(new_row);
    }
    return new_matrix;
}

// Creates and returns the <row, col> minor matrix (0 indexed).
//
vector<vector<tuple<string*,double>>*>* minor_matrix(vector<vector<tuple<string*,double>>*>* matrix, double row, double col)
{
    vector<vector<tuple<string*,double>>*>* minor = new vector<vector<tuple<string*,double>>*>();
    for (int i = 0; i < matrix->size(); i++) // row
    {
        if (i == row) continue; // skip row i
        vector<tuple<string*,double>>* new_row = new vector<tuple<string*,double>>();
        for (int j = 0; j < matrix->size(); j++) // col
        {   
            if (j == col) continue; // skip column j
            new_row->push_back(matrix->at(i)->at(j));
        }
        minor->push_back(new_row);
    }
    return minor;
}

// Returns the determinant of the given 2x2 matrix (tuple<general equation, actual value>).
//
tuple<string*,double> two_by_two_determinant(vector<vector<tuple<string*,double>>*>* matrix)
{
    string determinant_str;
    double determinant_double;

    tuple<string*,double> a11 = matrix->at(0)->at(0);
    tuple<string*,double> a12 = matrix->at(0)->at(1);
    tuple<string*,double> a21 = matrix->at(1)->at(0);
    tuple<string*,double> a22 = matrix->at(1)->at(1);

    // general equation = a11a22 - a12a21
    determinant_str = "(" + *(get<0>(a11)) + *(get<0>(a22)) + " - " + *(get<0>(a12)) + *(get<0>(a21)) + ")";

    // determinant_double = a11a22 - a12a21
    determinant_double = (get<1>(a11) * get<1>(a22)) - (get<1>(a12) * get<1>(a21));

    return make_tuple(new string(determinant_str), determinant_double);
}

// Returns the determinant of the given matrix (tuple<general equation, actual value>).
//
// Uses a 1st row cofactor expansion.
tuple<string*,double> determinant(vector<vector<tuple<string*,double>>*>* matrix)
{
    if (matrix->size() == 2)    {   return two_by_two_determinant(matrix);  }

    string determinant_str; // General equation (ie: a11a22-a21a12)
    double determinant_double = 0; // Actual value

    for (int col = 0; col < matrix->size(); col++) // Traverse first row
    {
        vector<vector<tuple<string*,double>>*>* minor = minor_matrix(matrix, 0, col);


        tuple<string*,double> det = determinant(minor);



        string minor_matrix_determinant_str = *(get<0>(det));
        double minor_matrix_determinant_double = get<1>(det);

        if (col % 2 == 1)
        {
            minor_matrix_determinant_str = "(-" + *(get<0>(matrix->at(0)->at(col))) + ")" + minor_matrix_determinant_str;
            minor_matrix_determinant_double *= -1;
        } else
        { 
            minor_matrix_determinant_str = "(" + *(get<0>(matrix->at(0)->at(col))) + ")" + minor_matrix_determinant_str;
        }
        

        if (col != 0) determinant_str += " + ";
        determinant_str += minor_matrix_determinant_str;

        minor_matrix_determinant_double *= get<1>(matrix->at(0)->at(col));
        determinant_double += minor_matrix_determinant_double;
    }

    return make_tuple(new string(determinant_str),determinant_double);

}

/**
 * @brief Returns both the value and closed-form equation for theinverse of a given matrix (3x3 or larger).
 * Returns null if matrix has no inverse, or size is < 3.
 * 
 * @param matrix A 2d vector of (string,double) tuples. The string represents the name of the entry (aij)
 * and the double represents the determinant_double. The string is included to allow for calculation of
 * the closed-form equation.
 */
vector<vector<tuple<string*,double>>*>* inverse(vector<vector<tuple<string*,double>>*>* matrix)
{
    if (matrix->size() <= 2) return nullptr;

    double major_determinant = get<1>(determinant(matrix));
    if (major_determinant == 0) return nullptr;
    
    vector<vector<tuple<string*,double>>*>* new_matrix = new vector<vector<tuple<string*,double>>*>();

    for (int row = 0; row < matrix->size(); row++)
    {
        vector<tuple<string*,double>>* new_row = new vector<tuple<string*,double>>();
        for (int col = 0; col < matrix->size(); col++)
        {
            vector<vector<tuple<string*,double>>*>* minor = minor_matrix(matrix, row, col);
            tuple<string*,double> minor_matrix_determinant_tup = determinant(minor);
            string minor_matrix_determinant_str = *(get<0>(minor_matrix_determinant_tup));
            double minor_matrix_determinant_double = get<1>(minor_matrix_determinant_tup);

            if ((row + col) % 2 == 1)
            {
                minor_matrix_determinant_double *= -1;
                minor_matrix_determinant_str = "(-1)" + minor_matrix_determinant_str;
            }
            minor_matrix_determinant_double /= major_determinant;

            new_row->push_back( make_tuple(new string( minor_matrix_determinant_str ), minor_matrix_determinant_double ) );
        }
        new_matrix->push_back(new_row);
    }

    return transpose(new_matrix);
}


extern "C"
{

/**
 * @brief Creates a matrix from a given string (comma and newline separated--ie: 3,3,3,\n,1,2,3,\n,1,2,3,
 * for a 3x3 matrix). Calls inverse() on the generated matrix, converts the returned matrix inverse
 * into a string, and returns the string.
 * 
 * This method exists only for javascript compatibility--Emscripten will convert this function into
 * Javascript. The generated code will run in a browser at near-native speeds. I anticipate that
 * this will be faster than a pure-JS version of the function, due to JS garbage collection.
 * Speed tests would be a good way to validate this.
 * 
 * This method is kind of nasty to read...
 * 
 * @param matrix_input string
 * @return string 
 */

const char* inverse_from_input_string(const char* matrix_input_ch)
{
    string matrix_input = matrix_input_ch;
    int row = 0; int col = 0;
    vector<vector<tuple<string*,double>>*>* matrix = new vector<vector<tuple<string*,double>>*>();
    vector<tuple<string*,double>>* curr_row = new vector<tuple<string*,double>>();

    // Set delimiter
    string delimiter = ",";
    while (matrix_input.size() != 0)
    {
        int found_delimiter = matrix_input.find(delimiter);
        if (found_delimiter == -1)
        {
            cerr<< "Inverse_from_input_string() error: Delimiter error--check input string";
            return "";
        }
        string token = matrix_input.substr(0, matrix_input.find(delimiter));
        

        if (token.compare("\n") == 0)
        {
            matrix->push_back(curr_row);
            curr_row = new vector<tuple<string*,double>>();
            col = 0;
            row++;
        } else
        {
            double token_as_double;
            try
            {
                { token_as_double = stod(token); } // Try to convert token to a double.
            }
            catch (const std::exception& e)
            {
                std::cerr << "An invalid input string was given.\n";
                return ""; // Returns empty string to Javascript
            }

            string* entry_name = get_entry_name(row,col);

            curr_row->push_back(make_tuple(entry_name,token_as_double));
            col++;
        }
        if (matrix_input.size() - 1 == found_delimiter) // If the last delimiter is found, break out of the loop.
        {
            matrix->push_back(curr_row);
            break;
        }

        // If the last delimiter is not found, found_delimiter + 1 must be in range.
        matrix_input = matrix_input.substr(found_delimiter + 1);
    }

    vector<vector<tuple<string*,double>>*>* matrix_inverse = inverse(matrix);

    string ret = "";

    if (!matrix_inverse) return ""; // If inverse() returned null, matrix has no inverse (or wrong size).

    for (int i = 0; i < matrix_inverse->size(); ++i)
    {
        for (int j = 0; j < matrix_inverse->size(); ++j)
        {
            double entry_as_double = get<1>(matrix_inverse->at(i)->at(j));
            ret += to_string(entry_as_double) + delimiter; // Each entry is added to the return string with a delimiter
        }
        ret += "\n" + delimiter; // After each row, a newline and a delimiter are added to the return string
    }

    const char* ret_ch = ret.c_str();
    return ret_ch;
}

}

int main()
{
    // string s = inverse_from_input_string("1.1,1,0,1,\n,0,0,2,3,\n,1,0,1,.5,\n,3.1,1.1,.5,0,");




    // Test code:
    

    vector<vector<tuple<string*,double>>*>* matrix = new vector<vector<tuple<string*, double>>*>();
    cout<<"dimension: ";
    int dimension;
    cin>>dimension;
    for (int i = 0; i < dimension; i++)
    {
        vector<tuple<string*,double>>* new_row = new vector<tuple<string*,double>>();
        for (int j = 0; j < dimension; j++)
        {
            cout<< *get_entry_name(i,j) + ": ";
            double val;
            cin >> val;
            string* name = get_entry_name(i,j);
            new_row->push_back(make_tuple(name, val));

        }
        matrix->push_back(new_row);
    }
    
    vector<vector<tuple<string*,double>>*>* inverse_matrix = inverse(matrix);
    for (int i = 0; i <dimension;i++)
    {
        for(int j = 0;j<dimension;j++)
        {
            cout<< get<1>(inverse_matrix->at(i)->at(j));
            cout<< "    ";
        }
        cout<<"\n";
    }

    
    return 1;
}












// Broken method:




// string inverse_from_input_string(string matrix_input)
// {
//     vector<vector<tuple<string*,double>>*>* matrix = new vector<vector<tuple<string*,double>>*>();
//     vector<tuple<string*,double>>* first_row = new vector<tuple<string*,double>>();

//     vector<tuple<string*,double>>* curr_row = first_row;
//     int row = 1;
//     int col = 1;

//     for (std::string::iterator it = matrix_input.begin(); it != matrix_input.end(); ++it)
//     {
//         if (*it == ',') // when a comma is found, the token between commas is extracted and converted to a double.
//         {
//             ++col; // col is iterated to allow entry names to be created
//             string* number_as_string = new string(matrix_input.begin(), it); // grab the number
//             double number_as_double;
//             try
//             {
//                 { number_as_double = stod(*number_as_string); } // try to convert the number to a double
//             }
//             catch(const std::exception& e)
//             {
//                 std::cerr << "An invalid input string was given.\n";
//                 return ""; // returns empty string to Javascript
//             }
//             string* entry_name = get_entry_name(row, col);
//             curr_row->push_back(make_tuple(entry_name, number_as_double));

//         } else
//         if (*it == '\n')
//         {
//             matrix->push_back(curr_row);
//             curr_row = new vector<tuple<string*,double>>();
//         } else
//         {

//         }
//     }


//     return "";
// }



