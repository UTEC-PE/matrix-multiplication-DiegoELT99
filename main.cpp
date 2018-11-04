#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <cmath>

#define DIMENSION 2

using namespace std;

int counter = 0;

int matrixA[DIMENSION][DIMENSION];
int matrixB[DIMENSION][DIMENSION];
int matrixM[DIMENSION][DIMENSION];

DWORD matrixMultiplication(LPVOID threadIndex)
{
    int i = (int)threadIndex;
    for(int j = 0; j < DIMENSION; j++)
    {
        int result = 0;

        for(int k = 0; k < DIMENSION; k++)
        {
            result += matrixA[i][k] * matrixB[k][j];
        }
        matrixM[i][j] += result;
    } 
}

void printMatrix(int matrix[DIMENSION][DIMENSION])
{
    for(int i = 0; i < DIMENSION; i++)
    {
        for(int j = 0; j < DIMENSION; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "---------------------------------------------------" << endl;
    cout << "Matrix Multiplication w/Threads ٩(◕‿◕｡)۶" << endl;
    cout << "---------------------------------------------------" << endl;

    for (int i = 0; i < DIMENSION; i++) { 
        for (int j = 0; j < DIMENSION; j++) { 
            matrixA[i][j] = rand() % 10; 
            matrixB[i][j] = rand() % 10; 
        } 
    } 

    DWORD threads[DIMENSION];
    HANDLE threadHandle[DIMENSION];

    int data[DIMENSION];

    for (int threadID = 0; threadID < DIMENSION; ++threadID) 
    {
        data[threadID] = threadID;
        threadHandle[threadID] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&matrixMultiplication, &data[threadID], 0, &threads[threadID]);
    }

    for (long threadID = 0; threadID < DIMENSION; ++threadID)
     {
        WaitForMultipleObjects(DIMENSION, threadHandle, TRUE, INFINITE);
    }
    
    /*printMatrix(matrixA);
    cout << endl;

    printMatrix(matrixB);
    cout << endl;

    printMatrix(matrixM);
    cout << endl;*/

}
