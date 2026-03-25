# UVa 10783 - Odd Sum

## Problem Description

給定一個區間 $[a, b]$，請計算該區間內所有 **奇數 (Odd numbers)** 的總和。
題目會有多組測試資料，每一組都需要依照 `Case i: sum` 的格式輸出結果。

**[Problem Link](https://onlinejudge.org/external/107/10783.pdf)**

---

## Learning Objectives
*   **Range Iteration**: 練習在指定區間內進行規律的累加運算。
*   **Parity Handling**: 學習如何判斷奇偶數，並對起始邊界進行微調。
*   **Case Tracking**: 練習處理計數型輸出（Case 1, Case 2...）。

---

## Solution Approach

### Algorithm Logic
這題的核心在於確保迴圈的「起點」是奇數。

1.  **處理起點**：如果 $a$ 是偶數，必須先將 $a$ 加 1 變成奇數，否則後續 `a += 2` 會導致整路都在加偶數。
2.  **累加過程**：從調整後的 $a$ 開始，只要 $a \le b$，就把 $a$ 加入總和，並讓 $a$ 跳 2 格（下一個奇數）。
3.  **狀態重置**：每處理完一個 Case，儲存總和的變數必須歸零，避免影響下一組測資。

### Code Evolution (原始 vs 修正)

在撰寫過程中，我針對起始值的邏輯進行了修正：


**原始代碼:**   `while (a <= b) { x += a; a += 2; }`   **存在風險**：若輸入的 $a$ 是偶數，會導致整組算出來都是偶數和。   
**修正代碼:**   `if (a % 2 == 0) a++;`    **正確**：強制將起點校正為奇數，確保邏輯穩健。

---

## Source Code

### 1. 原始程式碼 
> **問題點**：缺少了起點奇偶性的判斷。若 $a$ 為偶數，累加結果會錯誤；且輸出格式缺少換行與正確空格。

```cpp
#include<iostream>
using namespace std;
int main() {
    int n, x = 0;
    int i;
    cin >> n;
    for (i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        while (a <= b) {
            x += a;
            a += 2; // 若 a 為偶數，此處會一直加偶數
        }
        cout << "Case" << " " << i << ": " << x; // 格式不完全符合要求
        x = 0;
    }
};
```

### 2. 修改後程式碼 
**[Code Link](https://github.com/Yili-1021/11402_CI002/blob/main/HomeWork/Week3_01_10783/code.cpp)**
> **改進**：加入了 if (a % 2 == 0) a++; 確保從奇數開始，並修正了輸出格式 
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;     // 測資筆數
    int x = 0; // 用來存每次的總和
    int i;

    // 1. 讀入總共有幾組測試資料
    if (!(cin >> n)) return 0;

    for (i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b; // 讀入區間 [a, b]

        // 2. 關鍵修正：如果 a 是偶數，就先加 1 變成奇數
        if (a % 2 == 0) a++; 

        // 3. 從 a 開始一路加到 b，每次跳 2 單位（只加奇數）
        while (a <= b) {
            x += a;
            a += 2; 
        }

        // 4. 依照題目要求的格式輸出結果
        cout << "Case " << i << ": " << x << endl;

        // 5. 下一筆測資前要將累加變數歸零
        x = 0;
    }

    return 0;
}
```
---
## Complexity Analysis

*   **Time Complexity**: $O(T \times \frac{N}{2})$  
    其中 $T$ 為測試資料組數，$N$ 為區間長度 ($b - a$)。因為迴圈每次跳 2 單位（只跑奇數），實際執行次數約為區間的一半。在 UVa 的資料範圍下，運算幾乎是瞬間完成。
*   **Space Complexity**: $O(1)$  
    僅使用了 `n`, `x`, `i`, `a`, `b` 等數個整數變數，記憶體空間佔用固定，不隨輸入規模增加。

---

## Notes & Reflection

### Challenges
*   **起始值的奇偶**：如果 $a$ 是偶數且直接進行 `a += 2` 的迴圈，會導致整路都在加偶數（例如 $a=2$，會加到 $2, 4, 6...$）。在原始程式碼中我忽略了這一點，修正版透過 `if (a % 2 == 0) a++;` 解決了這個邏輯漏洞。
*   **輸出格式要求**：UVa 對格式（空格、冒號、換行）非常要求。例如 `Case 1: 13`，如果漏掉空格或沒換行都會導致 **Presentation Error** 或 **Wrong Answer**。

### Improvement
*   **預處理邏輯**：與其在迴圈內判斷 `if (a % 2 != 0)`，不如在進入迴圈前就先將 $a$ 校正為奇數。這樣可以讓 `while` 迴圈內部的邏輯更單純。
*   **變數重置**：在 `for` 迴圈末尾將 `x` 歸零（`x = 0`）確保了每一筆 Case 的計算都是獨立且正確的。

### What I Learned
*   **數學思維**：雖然這題用迴圈解很快，但我也思考了「等差數列」的求和公式，未來若遇到區間極大的題目，可以用數學方式達成 $O(1)$ 的最優解。
