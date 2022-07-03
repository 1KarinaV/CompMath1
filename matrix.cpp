#include <iostream>
#include <cmath>
using namespace std;
#include <fstream>
#include <string>



int readMatrixFromFile(double matrix[20][20], int n)
{
    ifstream fin("/Users/karinavladykina/Desktop/Computational_Math/Lab1.zip/matrix.txt");
    for (int i = 0; i < n; ++i)
    {
        for (int k = 0; k < n; ++k)
        {
            fin >> matrix[i][k];

        }
    }
}

int readBFromFile(double b[20], int n){
    ifstream fin("/Users/karinavladykina/Desktop/Computational_Math/Lab1.zip/b.txt");
    for (int i = 0; i < n; ++i) {
        fin >> b[i];
    }
}

bool compareMainDiagonal(int n, double matrix[20][20]){
    double neighbors;
    double compared;
    int status = 1;
    for (int i = 0; i < n; ++i)
    {
        neighbors = 0;
        compared = matrix[i][i];
        for (int j = 0; j < n; ++j)
        {
            neighbors = neighbors + matrix[i][j];
        }
        neighbors = neighbors - compared;

        if(abs(compared) >= abs(neighbors))
        {
            status = 1;
            cout <<"module of "<< compared << " bigger than neighbors " << endl;
        }
        else
        {
            status = 0;
            cout <<"module of "<< compared << " less than neighbors " << endl;
        }
    }

    return (status == 1);
}
double fillRandomMatrixA(int n, double matrix[20][20])
{
    double sum = 0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            matrix[i][i] = rand() * 200 - 100;

            if(1 != j)
            {
                sum += abs(matrix[i][j]);
            }
        }
        while (matrix[i][i] <= sum)
        {
                matrix[i][i] = rand() * 200 - 100 + sum;
        }

    }
}

double fillRandomB(double b[20], int n)
{
    for(int i=0; i<n; i++) {
        b[i] = rand() * 200 - 100;

    }
}

bool endingCondition(double currentValues[20], double lastValues[20], int n, double accuracy)
{
    double delta = 0;
    for (int i = 0; i < n; i++)
        delta += (currentValues[i] - lastValues[i]) * (currentValues[i] - lastValues[i]);
    return (sqrt(delta) < accuracy);
}


int main()
{
    int choice;
    double accuracy;
    double matrix[20][20];
    double b[20], x[20], p[20];
    int n, i, j, m = 0;

    //Entering Size
    cout << "Enter the size of the square matrix: " << endl;
    cin >> n;
    cout << "The size of matrix equals: ";
    cout << n << endl;


    //Entering Accuracy
    cout << "Enter the calculation precision: " << endl;
    cin >> accuracy;
    cout << "The accuracy equals: ";
    cout << accuracy << endl;


    //Entering Matrix
    cout << "Fill in matrix A: " << endl << endl;
    cout << "  You want to enter from: file - print 0, random- print 1. Else print any number : " << endl;
    cin >> choice;
    if(choice == 0){
        readMatrixFromFile(matrix, n);
    }
    else if (choice == 1) {
        fillRandomMatrixA(n, matrix);
    }
        else{
            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++)
                {
                    cout << "A[" << i << "][" << j << "] = ";
                    cin >> matrix[i][j];
                }
            cout << endl << endl;
        }

    cout << "Your matrix A: " << endl << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    //Entering B
    cout << "Fill in the free members column: " << endl << endl;
    cout << "   You want to enter from: file - print 0, random- print 1. Else print any number: " << endl;
    cin >> choice;
    if(choice == 0){
        readBFromFile(b, n);
    }
    else if (choice == 1){
        fillRandomB(b, n);
    }
    else{
        for (i = 0; i < n; i++)
        {
            cout << "В[" << i + 1 << "] = ";
            cin >> b[i];
        }
    }
    for (i = 0; i < n; i++) {
        cout << "В[" << i + 1 << "] = ";
        cout << b[i]<<endl;
    }
    cout << endl << endl;

    for (int i = 0; i < n; i++)
        x[i] = 1;
    cout << "Diagonal dominance: " << endl;
    if (compareMainDiagonal(n, matrix)) {
        do
        {
            for (int i = 0; i < n; i++)
                p[i] = x[i];
            for (int i = 0; i < n; i++)
            {
                double var = 0;
                for (int j = 0; j < i; j++)
                    var += (matrix[i][j] * x[j]);
                for (int j = i + 1; j < n; j++)
                    var += (matrix[i][j] * p[j]);
                x[i] = (b[i] - var) / matrix[i][i];
            }
            m++;
        } while (!endingCondition(x, p, n, accuracy));

        for (int k = 0; k < n; ++k) {
            cout << "Vector: ";
            cout << "x";
            cout << k+1 << endl;
            cout << "|";
            cout << x[k];
            cout << " - ";
            cout << p[k];
            cout << "|";
            cout << "=";
            cout << x[k] - p[k] << endl;
        }
        cout << "System solution:" << endl;
        for (i = 0; i < n; i++) {
            cout << "x" << i << " = " << x[i] << "" << endl;
        }
        cout << "Iterations: " << m << endl;
    }
    else {
        cout << "Dominance of diagonals is not fulfilled" << endl;
    }

    return 0;
}
