# UVa 10035-Primary Arithmetic

## Overview
**Overview: Determine how many carry operations occur when adding two integers.**

## Input Description
Each line of input contains two positive integers, each with up to 10 digits. The last line of input will be 0 0, which indicates the end of the input and should not be processed.
**example:**  
123 456  
555 555  
123 594  
0 0  
## Output Description
For each line of input, output the number of carry operations that occur when adding the two integers.  
**example:**  
No carry operation.  
3 carry operations.  
1 carry operation.  
## My Code
```cpp
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
```
## Main Problems
**進位判斷邏輯不完整**  
- 只判斷 i + j >= 10，但沒有考慮「前一位的進位」會影響下一位。  
- 正確做法是要有一個 carry 變數，記錄前一次的進位，並加到下一位的計算中。  
**進位計數器未重置**  
- 如果輸入多組測資，x 會累積上一次的結果。  
- 必須在每次輸出後重置 x = 0;  
## Improved Code
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    while (cin >> a >> b && !(a == 0 && b == 0)) {
        int carry = 0;  
        int count = 0;  

        while (a > 0 || b > 0) {
            int i = a % 10;
            int j = b % 10;

            if (i + j + carry >= 10) {
                count++;
                carry = 1;   
            } else {
                carry = 0;
            }

            a /= 10;
            b /= 10;
        }

        if (count == 0)
            cout << "No carry operation." << endl;
        else
            cout << count << " carry operations." << endl;
    }
    return 0;
}
```
