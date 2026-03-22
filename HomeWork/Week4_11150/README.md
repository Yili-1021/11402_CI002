#  UVa 11150 - Cola


##  Problem Description

你有n瓶可樂，每 **3 個空瓶**可以換 **1 瓶**新的可樂。你想知道在「可以借空瓶（但最後必須還回去）」的情況下，最多能喝到幾瓶可樂？

**[Problem Link](https://zerojudge.tw/ShowProblem?problemid=d189)**

---

## Learning Objectives

**Understand Greedy Thinking**: 學習如何透過「借與還」的邏輯極大化收益。
**Implement Iterative Logic**: 使用 `while` 迴圈模擬重複兌換過程。
**Practice I/O Handling**: 使用 `while (cin >> n)` 處理多組測試資料直到檔案結束 (EOF)。

---

##  Solution Approach

### Algorithm Logic
你最多可以向朋友借 **2 個空瓶**（因為如果你借了並湊成 3 個，換回 1 瓶喝完後剛好剩 1 個空瓶，還掉後你不會欠債）。

1. **讀取輸入**：持續讀取整數 n。
2. **模擬過程**：
   * 初始喝掉的數量為 $n$。
   * 當 `empty_bottles >= 3` 時，不斷進行兌換：
     * `new_cola = empty_bottles / 3`
     * `total += new_cola`
     * `empty_bottles = (empty_bottles % 3) + new_cola`
3. **處理「借」的邏輯**：
   * **關鍵觀察**：當最後手上有 2 個空瓶時，借 1 個湊成 3 個，換 1 瓶喝完後剛好把那 1 個空瓶還給朋友。

### Key Insights
只要手上的空瓶還夠換（也就是 empty >= 3），就可以一直換下去。 
想辦法簡化「借」與「還」


---

## Source Code
**[Code Link](https://github.com/Yili-1021/11402_CI002/blob/main/HomeWork/Week4_11150/code.cpp)**

```cpp
#include <iostream>

using namespace std;

```cpp
#include <iostream>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int em = n;   // 當前空瓶數
        int tol = n;  // 總共喝掉的可樂數
        
        // 模擬正常兌換
        while (em >= 3) {
            int newcola = em / 3;
            tol += newcola;
            //更新手邊剩下的空瓶 新喝完的 + 剛才湊不滿 3 個留下的
            em = em % 3 + newcola;
        }
        
        // 處理借瓶子情況：剩 2 個可以借 1 個湊 3 個，喝完還 1 個
        if (em == 2) {
            tol++;
        }
        
        cout << tol << endl;
    }
    return 0;
}
```
---

## Complexity Analysis



**Time Complexity:**  $O(\log_3 n)$  每次循環空瓶數都會大幅減少，執行效率極高。 

**Space Complexity:**  $O(1)$  僅使用了 `em` 與 `tol` 兩個整數變數，空間佔用極小。 

---

## Notes & Reflection

* **Challenges**
  * 剛開始可能會猶豫「借瓶子」這個動作要如何轉化為程式碼。
  * 後來發現不需要真的寫一個「借」與「還」的複雜函數，只要用 if(em==2) tol++。
* **Improvement**
  * 程式碼中的 `em = em % 3 + newcola` 寫法非常精確，完整還原了現實中「剩餘空瓶 + 剛喝完的空瓶」的兌換場景。
  * 也可以直接用數學規律 $total = \lfloor \frac{3n}{2} \rfloor$ 解決。
* **What I Learned**
  * 學習到如何將題目中的條件簡化處理。
  * 練習了使用 `while (cin >> n)` 處理連續輸入的技巧。

---
