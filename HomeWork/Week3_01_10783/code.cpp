#include<iostream>
using namespace std;

int main() {
    int n; // 測資筆數
    int x = 0; // 用來存每次的總和
    int i;

    cin >> n; // 先讀測資筆數
    for (i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b; // 讀入區間 [a, b]

        // 從 a 開始一路加到 b
        // 只加奇數
        if (a % 2 == 0) a++; // 如果 a 是偶數，就先加 1 變成奇數
        while (a <= b) {
            x += a;
            a += 2; // 每次跳到下一個奇數
        }

        // 輸出結果，格式要符合題目要求
        cout << "Case " << i << ": " << x << endl;

        // 下一筆測資要歸零
        x = 0;
    }

    return 0;
}
