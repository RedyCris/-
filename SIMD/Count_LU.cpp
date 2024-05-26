#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>
using namespace std;

int N = 2048;

vector<vector<double>> m(N, vector<double>(N, 0.0)); // ��ʼ��ȫ�־��� m
vector<vector<double>> L(N, vector<double>(N, 0.0)); // ����Lower����
vector<vector<double>> U(N, vector<double>(N, 0.0)); // ����Upper����

void printMatrix(const vector<vector<double>>& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void m_reset() {
    // ��ʼ�� m Ϊ��λ����������
    srand(time(nullptr)); // �����������

    for (int i = 0; i < N; i++) {
        m[i][i] = 1.0; // �Խ���Ԫ��Ϊ 1.0

        for (int j = i + 1; j < N; j++) {
            m[i][j] = rand() / (double)RAND_MAX; // �ǶԽ���Ԫ��Ϊ 0 �� 1 ֮��������
        }
    }

    // �ۼӲ���
    for (int k = 0; k < N; k++) {
        for (int i = k + 1; i < N; i++) {
            for (int j = 0; j < N; j++) {
                m[i][j] += m[k][j];
            }
        }
    }
}

void croutLuDecomposition(vector<vector<double>>& mat, vector<vector<double>>& lower, vector<vector<double>>& upper) {
    int n = mat.size();

    for (int i = 0; i < n; i++) {
        lower[i][i] = 1.0;

        for (int j = i; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) {
                sum += lower[i][k] * upper[k][j];
            }
            upper[i][j] = mat[i][j] - sum;
        }

        for (int j = i + 1; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) {
                sum += lower[j][k] * upper[k][i];
            }
            lower[j][i] = (mat[j][i] - sum) / upper[i][i];
        }
    }
}

int main() {
    m_reset();
    int iterations = 1;

    using namespace std::chrono;
    double count = 0;

    for (int i = 0; i < iterations; ++i)
    {
        m_reset();
        auto start = steady_clock::now();
        croutLuDecomposition(m, L, U);
        auto end = steady_clock::now();
        duration<double, milli> duration = end - start;
        count += duration.count();
    }
    cout << "Crout-LU: " << count << "ms" << endl;

    /*cout << "Lower triangular matrix L:" << endl;
    printMatrix(L);

    cout << "Upper triangular matrix U:" << endl;
    printMatrix(U);*/

    return 0;
}