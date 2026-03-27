# UVa 10170 - The Hotel with Infinite Rooms

## Problem Description
有一間擁有無限房間的旅館，房間編號從 1 開始。  
每天會有一批新客人入住，第一天有 `s` 個人，第二天有 `s+1` 個人，第三天有 `s+2` 個人，以此類推。  

給定兩個整數 `s` 和 `d`：  
- `s` 表示第一天入住的人數。  
- `d` 表示要找到第幾天，累積入住人數達到或超過 `d`。  

**[Problem Link](https://onlinejudge.org/external/101/10170.pdf)**

---

## Learning Objectives
- **累加思維**：透過迴圈逐步累加，直到達到指定目標。  
- **條件判斷**：判斷累積值是否超過目標，並立即輸出答案。  
- **模擬過程**：熟悉如何用簡單迴圈模擬數學過程。  

---

## Solution Approach

### Algorithm Logic
1. 初始化 `sum = 0`，從第 `s` 天開始。  
2. 每天累加當天入住人數。  
3. 當累積人數 `sum >= d` 時，輸出當天的編號並結束迴圈。  
4. 重複處理多組測資直到 EOF。  

---

## Source Code
**[Code Link](https://github.com/Yili-1021/11402_CI002/blob/main/HomeWork/Week3_02_10107/code.cpp)**
```cpp
#include <iostream>
using namespace std;

int main() {
    int s, d;
    // 用 while 讀到 EOF
    while (cin >> s >> d) {
        int sum = 0; // 累積入住人數
        // 從第 s 天開始，每天入住人數依序增加
        for (int day = s;; day++) {
            sum += day; // 累加當天入住人數
            if (sum >= d) {
                // 當累積人數達到或超過 d，輸出當天編號
                cout << day << endl;
                break; // 結束迴圈，處理下一筆測資
            }
        }
    }
    return 0;
}

```
---
## Complexity Analysis
- **Time Complexity**: O(d - s)  
  在最壞情況下，必須從第 s 天一路累加到某一天，使得總和達到或超過 d。迴圈次數大約等於 (d - s)，所以時間複雜度是線性的。  
- **Space Complexity**: O(1)  
  僅使用 sum、day 等少量變數，記憶體固定。

---

## Notes & Reflection

### Challenges
- 必須正確理解題意：每天入住人數是遞增的，而不是固定的。  
- 若沒有正確判斷 `sum >= d`，可能會陷入無窮迴圈。  

### Improvement
- 可以用數學公式（等差數列求和公式）直接計算，避免逐步累加。    
### What I Learned
- **模擬與數學的平衡**：這題用迴圈模擬很直觀，但也能用公式快速解。  
- **正確性優先**：先用簡單方法確保正確，再思考是否需要優化。  
- **題意理解的重要性**：仔細讀題，避免誤解「每天入住人數」的規則。  
