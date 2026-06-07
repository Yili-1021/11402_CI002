# UVa 100 - The 3n+1 Problem

## Problem Description
給定一個區間 [i, j]，對區間內的每個數字計算其 **cycle length**（Collatz conjecture 過程長度），並輸出該區間的最大 cycle length。  

Cycle length 的定義：  
- 若數字是偶數，則除以 2。  
- 若數字是奇數，則變成 3n+1。  
- 重複直到數字變成 1，過程中每一步都算一次。  

**[Problem Link](https://onlinejudge.org/external/1/100.pdf)**

---

## Learning Objectives
- **Brute Force Simulation**: 練習直接模擬題目定義，不使用快取或數學優化。  
- **Range Handling**: 學習如何處理區間輸入，包含 i > j 的情況。  
- **Cycle Length Calculation**: 熟悉 Collatz conjecture 的迴圈邏輯。  

---

## Solution Approach

### Algorithm Logic
1. 保留原始輸入，因為輸出要照題目要求顯示原始的 i, j。  
2. 若 i > j，交換兩者，確保區間正確。  
3. 對區間內每個數字，模擬 Collatz 過程直到變成 1，計算 cycle length。  
4. 記錄 cycle length 的最大值。  
5. 輸出原始 i, j 和最大 cycle length。  

---

## Source Code
**[Code Link](https://github.com/Yili-1021/11402_CI002/blob/main/HomeWork/Week1_01_100/code.cpp)**
```cpp
#include <iostream>
using namespace std;

int main() {
    long long i, j;
    // UVa 100 會有多組輸入，所以用 while 讀到 EOF
    while (cin >> i >> j) {
        long long start = i, end = j; // 保留原始輸入
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
```
---
## Complexity Analysis
- **Time Complexity**: O(N × L)  
  其中 N = j - i + 1，L 為單個數字的 cycle length。每個數字都完整模擬，效率不高，但在 UVa 的範圍內仍可接受。  
- **Space Complexity**: O(1)  
  僅使用少量變數，記憶體固定。  

---

## Notes & Reflection

### Challenges
- **效率問題**：沒有快取，對大區間可能會慢，但仍能過題。  
- **區間處理**：必須注意 i > j 的情況，否則會出錯。  

### Improvement
- 可以用 memoization 儲存已算過的 cycle length，避免重複計算。  
- 思考更高效的數學方法，仍有優化空間。  

### What I Learned
- **正確性優先**：先用暴力解法確保正確，再思考優化。  
- **格式嚴謹**：UVa 對輸出格式要求非常嚴格，必須完全符合。  
- **逐步提升**：解題過程中能體會「先解決問題，再改善效率」的思維方式。  
