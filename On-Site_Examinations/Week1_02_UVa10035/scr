#include <iostream>
using namespace std;

int main() {
    int a, b;          // 宣告兩個整數 a、b，代表要相加的數字
    int x = 0;         // 用來計算「進位」的次數

    // 錯誤：這裡應該是 `cin >> a >> b`，而不是 `cin << a << b`
    while (cin >> a >> b) {  

        // 這裡應該要檢查 a 和 b 是否都不是零，否則結束
        while (a || b) {
            // 錯誤：這裡應該先取出 a 和 b 的「個位數」
            int i = a % 10;   // 取出 a 的個位數
            int j = b % 10;   // 取出 b 的個位數

            // 如果兩個位數相加 >= 10，代表需要進位
            if (i + j >= 10)
                x++;

            // 把 a、b 去掉個位數，繼續檢查下一位
            a /= 10;
            b /= 10;
        }

        // 輸出結果
        if (x == 0) {
            cout << "No carry operation." << endl;
        } else {
            cout << x << " carry operations." << endl;
        }

        // 重置 x，避免影響下一組輸入
        x = 0;
    }
}
