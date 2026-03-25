# UVa 490 - Rotating Sentences

## Problem Description

想像你有一疊橫向書寫的句子，這題要求將這疊紙「順時針旋轉 90°」後印出來。旋轉後，原本的第一行會變成最後一列，最後一行則變成第一列。

**關鍵規則：** 
如果旋轉後的某個位置在原本的句子中不存在（因為各行長度不同），必須輸出一格 **「空格」** 來填補位子，否則排版會崩潰。

**[Problem Link](https://onlinejudge.org/external/4/490.pdf)**

---

## Learning Objectives
*   **2D Matrix Transposition**: 學習如何透過變換迴圈達成矩陣旋轉。
*   **String Handling**: 處理長短不一的字串輸入，練習使用 `getline()`。
*   **Padding Logic**: 實作「補位」邏輯以維持輸出格式的完整性。

---

## Solution Approach

### Algorithm Logic
這題的核心不需要真的去更動記憶體中的資料位置，只要改變 **「讀取的順序」** 就能達成旋轉效果。

1.  **資料收集**：使用 `getline(cin, L[c])` 讀取每一行文字，並記錄下所有句子中最長的長度 `m`。
2.  **縱向掃描**：
    *   **外層迴圈**：走訪「字元位置」（原本的 Column），從 0 到 $m-1$。
    *   **內層迴圈**：走訪「句子編號」（原本的 Row），**從最後一行倒著走回第一行**（這是順時針 90° 的關鍵）。
3.  **條件輸出**：
    *   若目前句子長度夠長，印出字元。
    *   若長度不足，補印一個空格。

### Key Insights
*   **虛擬旋轉**：透過 `L[row][col]` 的索引變換，我們在輸出時直接完成旋轉，節省了空間與運算時間。
*   **補位的重要性**：若不補空格，後方的字元會因為縮排而移位，導致結果錯誤。

---

## Source Code

**[Code Link](https://github.com/Yili-1021/11402_CI002/blob/main/HomeWork/Week2_02_490/code.cpp)**

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string L[105]; // 儲存每一行文字
    int m = 0;     // 紀錄最長句子的長度
    int c = 0;     // 紀錄總行數

    // 1. 讀取輸入直到 EOF
    while (getline(cin, L[c])) {
        if ((int)L[c].size() > m) {
            m = L[c].size(); // 更新全域最長長度
        }
        c++; 
    }

    // 2. 座標轉換輸出
    // col 代表旋轉後的行數 (原本字串中的字元位置)
    for (int col = 0; col < m; col++) {
        // row 代表原本的第幾個句子，從最後一行倒著讀回去
        for (int row = c - 1; row >= 0; row--) {
            // 如果這行長度夠，就印出字元
            if (col < (int)L[row].size()) {
                cout << L[row][col];
            }
            // 否則補空格，維持矩陣形狀
            else {
                cout << " ";
            }
        }
        cout << endl; // 每一列輸出完畢後換行
    }

    return 0;
}
```
---

## Complexity Analysis

*   **Time Complexity**: $O(M \times C)$  
    其中 $M$ 是所有句子中最長的字元數，$C$ 是總行數。程式必須走訪這個由 $M$ 欄與 $C$ 列組成的虛擬矩陣，每個位置都剛好經過一次判斷與輸出，因此執行時間與矩陣面積成正比。
*   **Space Complexity**: $O(N)$  
    我們使用了一個字串陣列來儲存所有輸入字元，空間消耗與輸入的總字元數 $N$ 成線性相關。

---

## Notes & Reflection

### Challenges
*   **補空格**：最初可能會想直接印出字元，但若短句子後面還有長句子，沒補空格會導致後方的字元全部往前移位。所以即使原本沒字的地方，旋轉後也要用空格撐住位置。
*   **座標轉置邏輯**：要把橫向改為縱向輸出，並確保第一行變成最後一列。外層迴圈跑字元位置，內層迴圈則要「倒著」跑句子編號。

### Key Learnings
*   **虛擬旋轉 (Virtual Rotation)**：這是我學到最重要的一點。不需要真的去搬移記憶體裡的資料，只要改變 `for` 迴圈的存取順序（Access Order），就能在輸出的瞬間達成旋轉的效果，這比搬動資料更有效率。
*   **I/O 的細節**：再次練習了 `getline()` 的用法，確保包含空格的句子能被完整讀入。

### Improvement
*   **型別安全**：在比較 `col < L[row].size()` 時，將 `size()` 強制轉型為 `int`，避免在不同編譯器下產生不必要的 Bug 或 Warning。
