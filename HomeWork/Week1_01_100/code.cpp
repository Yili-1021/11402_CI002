#include <iostream>
using namespace std;

int main() {
    long long i, j;
    //用 while 讀到 EOF
    while (cin >> i >> j) {
        long long start = i, end = j; 
        if (i > j) swap(i, j);        // 如果 i > j，要交換

        int maxCycle = 0; // 記錄最大 cycle length

        // 從 i 到 j，每個數字都算一次 cycle length
        for (long long k = i; k <= j; k++) {
            long long n = k;
            int length = 1; // 起始數字本身也算一步

            // 模擬 Collatz 過程
            while (n != 1) {
                if (n % 2 == 0) {
                    n = n / 2;       // 偶數：除以 2
                } else {
                    n = 3 * n + 1;   // 奇數：3n+1
                }
                length++; // 每次轉換算一步
            }

            // 更新最大值
            if (length > maxCycle) {
                maxCycle = length;
            }
        }

        // 輸出格式：原始 i j 最大 cycle length
        cout << start << " " << end << " " << maxCycle << endl;
    }
    return 0;
}
