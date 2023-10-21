#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;

/*Struct that stores data about the matrices read from the given file.*/
struct Data
{
    int size;
    int **matrix_1;
    int **matrix_2;
};

// Function Prototypes (I tried to put the struct here as well, but it is required for where it is.)
Data matrixLoad(string filename);
void matrixPrint(int **matrix, int size);
int **matrixAdd(Data data);
int **matrixSubtract(Data data);
int **matrixProduct(Data data);

int main() {
    //--HEADING--//
    cout << "Riley Meyerkorth" << endl;
    cout << "Lab #6: Matrix Manipulation" << endl;

    //--STEP 1--//
    // Load matrices from file
    Data data = matrixLoad("matrix.txt");
    int size = data.size;
    int** matrix_1 = data.matrix_1;
    int** matrix_2 = data.matrix_2;
    cout << "Matrix Sizes: " << size << " x " << size << endl;

    //--STEP 2--//
    cout << "\nMatrix A" << endl;
    matrixPrint(matrix_1, size);
    cout << "Matrix B" << endl;
    matrixPrint(matrix_2, size);

    //--STEP 3--//
    cout << "Matrix Sum (A + B)" << endl;
    int **addedMatrix = matrixAdd(data);
    matrixPrint(addedMatrix, size);

    //--STEP 4--//
    cout << "Matrix Product (A * B)" << endl;
    int **productMatrix = matrixProduct(data);
    matrixPrint(productMatrix, size);

    //--STEP 5--//
    cout << "Matrix Difference (A - B)" << endl;
    int **subtractedMatrix = matrixSubtract(data);
    matrixPrint(subtractedMatrix, size);

    // Return from main
    return 0;
}

/* Loads 2 matrices in from a text file and returns an array containing the size and both matrices*/
Data matrixLoad(string filename) {
    // Initialize Variables
    ifstream file;
    string text;
    int size;
    static const int maxSize = 100;
    int line = 1;
    
    // Open file
    file.open(filename);

    // Get the first line to get the size
    getline(file, text);
    size = atoi(text.c_str());

    // Check against max size
    if (size > maxSize)
    {
        printf("ERROR: Size of square matrix must be less than %i!", maxSize);
        terminate();
    }

    // Allocate memory for matrices
    int **matrix_1 = new int*[size];
    int **matrix_2 = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix_1[i] = new int[size]();
        matrix_2[i] = new int[size]();
    }
    
    while (getline(file, text)) {
        istringstream iss(text);
        int col = 0;
        int value;

        // Reading the first matrix
        if (1 <= line && line <= size) {
            while (iss >> value) {
                matrix_1[line-1][col++] = value;
            }
        }

        // Reading the second matrix
        if ((size + 1) <= line && line <= (size * 2)) {
            while (iss >> value) {
                matrix_2[line-(size+1)][col++] = value;
            }
        }

        line++;
    }

    // Close file
    file.close();

    // Return the matrices
    Data result {size, matrix_1, matrix_2};
    return result;
}

/* Cleanly prints a given matrix*/
void matrixPrint(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%5i", matrix[i][j]);
        }
        printf("\n");
    }
}

/* Adds 2 matrices together and returns a single matrix */
int **matrixAdd(Data data)
{
    // Initialize variables
    int size = data.size;
    int **matrix_1 = data.matrix_1;
    int **matrix_2 = data.matrix_2;

    // Allocate memory for resulting
    int **result = new int*[size];
    for (int i = 0; i < size; ++i) {
        result[i] = new int[size]();
    }

    // Sum every value in the matrix
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int value = matrix_1[i][j] + matrix_2[i][j];
            result[i][j] = value;
        }
    }

    return result;
}

/* Subtracts 2 matrices and returns a single matrix */
int **matrixSubtract(Data data)
{
    // Initialize variables
    int size = data.size;
    int **matrix_1 = data.matrix_1;
    int **matrix_2 = data.matrix_2;

    // Allocate memory for resulting
    int **result = new int*[size];
    for (int i = 0; i < size; ++i) {
        result[i] = new int[size]();
    }

    // Subtract every value in the matrix
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int value = matrix_1[i][j] - matrix_2[i][j];
            result[i][j] = value;
        }
    }

    return result;
}

/* Multiplies 2 matrices together and returns a single matrix */
int **matrixProduct(Data data)
{
    // Initialize variables
    int size = data.size;
    int **matrix_1 = data.matrix_1;
    int **matrix_2 = data.matrix_2;

    // Allocate memory for resulting
    int **result = new int*[size];
    for (int i = 0; i < size; ++i) {
        result[i] = new int[size]();
    }

    // Perform matrix multiplication
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                result[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }

    return result;
}