#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "omp.h"
#include <ctime> 

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    int i, j, n, m;

    //������� ������
    cout << "����� ����� ���������: ";
    cin >> n;
    cout << "����� ����� �����������: ";
    cin >> m;
    m += 1;
    float** matrix = new float* [n];
    for (i = 0; i < n; i++)
        matrix[i] = new float[m];

    //��������������

    for (i = 0; i < n; i++)

        for (j = 0; j < m; j++)
        {
            matrix[i][j]=rand();
        }

    //������� ������
    cout << "matrix: " << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    //����� ������
    //������ ���, ���������� � ������������������ ����
    float  tmp;
    int k;
    float* xx = new float[m];
    omp_set_num_threads(2);
    for (i = 0; i < n; i++)
    {
        tmp = matrix[i][i];
        for (j = n; j >= i; j--)
            matrix[i][j] /= tmp;
#pragma omp parallel for private (j, k, tmp)
        for (j = i + 1; j < n; j++)
        {
            tmp = matrix[j][i];
            for (k = n; k >= i; k--)
                matrix[j][k] -= tmp * matrix[i][k];
        }
    }
    /*�������� ���*/
    xx[n - 1] = matrix[n - 1][n];
    for (i = n - 2; i >= 0; i--)
    {
        xx[i] = matrix[i][n];
        for (j = i + 1; j < n; j++) xx[i] -= matrix[i][j] * xx[j];
    }

    //������� �������
    for (i = 0; i < n; i++)
        cout << xx[i] << " ";
    cout << endl;

    cout << "runtime = " << clock() / 1000.0 << endl;

    delete[] matrix;
    return 0;
}