#include <iostream>
#include <chrono>
using namespace std;
#define ull unsigned long long int
const int N = 5000;
ull matrix[N][N];
ull vector[N];
// �������ÿ��������������ڻ���cache�Ż��㷨��
ull* columnVectorInnerProductCacheOptimized() {
    static ull result[N] = { 0 }; // �ڻ�����洢����

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            result[row] += matrix[row][col] * vector[col];
        }
    }
    return result;
}
 
int main() {
    // �Ծ���ֵ
    for (int i = 0; i < N; ++i) {
        vector[i] = i;
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = i * N + j; // ������Ը����������ı丳ֵ�߼�
        }
    }

    
    int iterations = 10; // �ظ�ִ���ڻ�����10000000��

    // ��ʼ��ʱ
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        ull* result = columnVectorInnerProductCacheOptimized();
    }
    // ������ʱ
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "10000000�μ�����ʱ��: " << duration.count() << " microseconds" << std::endl;
    cout << endl;

    return 0;
}