# UVa 272 - TeX Quotes

## Problem Description
在 LaTeX 排版系統中，雙引號有區分「左引號」與「右引號」。本題要求將輸入文本中成對出現的雙引號 (`"`) 進行轉換：
*   **第 1, 3, 5... 次**出現的 `"` 替換為兩個反引號 (`` `` `` ``)。
*   **第 2, 4, 6... 次**出現的 `"` 替換為兩個單引號 (`''`)。

**[Problem Link](https://zerojudge.tw/ShowProblem?problemid=c007)**

---

## Learning Objectives
*   **State Management**: 學習使用 `bool` 變數作為旗標（Flag）來進行狀態切換。
*   **Character-level I/O**: 練習使用 `cin.get()` 處理包含空白與換行的原始文本。
*   **Toggle Logic**: 實作非此即彼的交替邏輯。

---

## Solution Approach

### Algorithm Logic
這是一個典型的**狀態機（State Machine）**概念，程式維護一個「目前是左引號還是右引號」的狀態。

1.  **初始化**：設定 `bool open = true`，代表下一個遇到的 `"` 是起始引號。
2.  **逐字讀取**：使用 `while (cin.get(x))` 讀取每一個字元（不可使用 `cin >> x`，否則空白與換行會消失）。
3.  **判斷與替換**：
    *   若遇到 `"` 且 `open` 為 `true`：輸出 `` `` `` ``，並將 `open` 設為 `false`。
    *   若遇到 `"` 且 `open` 為 `false`：輸出 `''`，並將 `open` 設為 `true`。
    *   其餘字元：直接原樣輸出。

### Key Insights
*   **不要用 `cin >> x`** 
    `cin >> x` 會忽略空格和換行，這會破壞原始文本的格式。`cin.get(x)` 能確保讀取到「每一個」字元。
*   **狀態切換**：`open = !open;` 是處理這類交替邏輯最簡潔的寫法。

---

## Source Code
**[Code Link](https://github.com/Yili-1021/11402_CI002/blob/main/HomeWork/Week2_01_272/code.cpp)**

```cpp

#include<iostream>
using namespace std;

int main() {

    char x;           // 一個字一個字讀進來
    bool open = true; // 用來記錄現在要印的是開頭還是結尾的引號
    while (cin.get(x)) { // 持續讀到檔案結束

        if (x == '"') {  // 遇到雙引號

            if (open) 
                cout << "``";   // 如果是開頭，就印兩個反引號
            else 
                cout << "''";   // 如果是結尾，就印兩個單引號

            open = !open;       // 換一下狀態，下次就反過來
        }
        else {
            cout << x;          // 不是引號就照原樣輸出
        }
    }
};
```
---
## Complexity Analysis

**Time Complexity**: $O(N)$  
    程式透過 `while (cin.get(x))` 遍歷輸入文本中的每一個字元，每個字元僅經過一次判斷與輸出，因此執行時間與輸入總字元數 $N$ 成線性比例。  
 **Space Complexity**: $O(1)$  
    僅使用了 `char x` 與 `bool open` 兩個變數。無論輸入文本多長，記憶體佔用量皆維持固定，不隨資料量增加。

---

## Notes & Reflection

### Challenges
**字元讀取的陷阱**：  
最初可能會直覺使用 `cin >> x`，但這會導致所有空白（Space）與換行符（Newline）被自動跳過，破壞原始文本格式。改用 `cin.get(x)` 是本題成功的關鍵。  
**跨行狀態保留**：  
引號的對應是全域的，並非每一行重新計算。使用 `bool` 旗標在 `while` 迴圈外部定義，可以確保狀態在處理多行輸入時持續有效。  

### Key Learnings
**狀態機基礎**：  
這題是狀態機（State Machine）的最簡化版本。透過布林值在「開啟 (Open)」與「關閉 (Closed)」兩個狀態間切換，處理交替出現的邏輯。  
**I/O 流的掌握**：  
理解了標準輸入流中 `get()`、`>>` 與 `getline()` 的行為差異，這對於處理不規則格式的字串題目非常重要。  

### Improvement
**效能優化**：  
在 C++ 中，`cin` 與 `cout` 相對較慢。若處理極大量數據，可以使用 C 語言的 `getchar()` 與 `putchar()`，或是加入 `ios::sync_with_stdio(0); cin.tie(0);` 來提升執行速度。  
**程式碼簡潔度**：  
利用 `open = !open` 的寫法比 `open = false` 搭配 `open = true` 少了邏輯冗餘。  
