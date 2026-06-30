# UVa 102 - Ecological Bin Packing

## 問題描述
有三個回收箱（簡稱第 1、2、3 箱），每個箱子裡原本都混雜著三種不同顏色的玻璃瓶：棕色（Brown）、綠色（Green）和透明色（Clear）。

我們的目標是移動最少數量的瓶子，使得最後**每個箱子都只裝有一種顏色的瓶子**，且**三個箱子的瓶子顏色各不相同**。

請找出搬移瓶子數量最少的顏色配置組合。如果有多組配置的搬移瓶子數量相同，請輸出**字典順序（Alphabetical Order）最小**的那一組字串（例如 `BCG` 優先於 `BGC`），並輸出對應的最少搬移步數。

---

## 解題邏輯與程式

### 核心邏輯
由於箱子只有 3 個，顏色也固定是 3 種，因此所有可能的顏色排列組合只有 $3! = 6$ 種。這 6 種可能的配置狀況分別為：
- `BCG`, `BGC`, `CBG`, `CGB`, `GBC`, `GCB`

既然組合數極少且固定，最穩健且有效率的方法就是**暴力枚舉法（Brute Force）**，直接依序計算這 6 種狀況的搬移成本：

1. **按字典序枚舉**：為了完美符合題目「步數相同時輸出字典序最小」的要求，我們直接按照 `BCG` 到 `GCB` 的字典順序依序檢查。這樣一來，後續比對時只要維持 `if (current_cost < min_cost)` 嚴格小於的條件，就能在同分時自然保留最早出現（字典序最小）的答案。
2. **成本計算技巧**：與其去想怎麼把瓶子「搬出去」，不如反過來思考**「有哪些瓶子可以留在原地不用動」**。
   - 總搬移步數 = 所有箱子的玻璃瓶總數 - 留在原地的玻璃瓶數。
   - 例如在 `BCG` 配置下（第 1 箱留 B、第 2 箱留 C、第 3 箱留 G）：
     $$\text{Cost} = \text{Total} - (B_1 + C_2 + G_3)$$

透過這種反向思考，可以讓每個組合的成本計算簡化成單純的加減法。

### 完整程式碼
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    // 儲存每個箱子的 B, G, C 數量
    // b1, g1, c1, b2, g2, c2, b3, g3, c3
    int b[4], g[4], c[4];

    while (cin >> b[1] >> g[1] >> c[1] >> b[2] >> g[2] >> c[2] >> b[3] >> g[3] >> c[3]) {
        // 計算所有瓶子的總數
        long long total = 0;
        for (int i = 1; i <= 3; i++) {
            total += b[i] + g[i] + c[i];
        }

        long long min_move = -1;
        string best_config = "";

        // 依據字典順序 (Alphabetical Order) 定義 6 種排列組合
        string configs[] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};

        for (const string& s : configs) {
            long long current_move = total;

            // 扣除各箱子指定留下的瓶子數量
            if (s == "BCG") current_move -= (b[1] + c[2] + g[3]);
            else if (s == "BGC") current_move -= (b[1] + g[2] + c[3]);
            else if (s == "CBG") current_move -= (c[1] + b[2] + g[3]);
            else if (s == "CGB") current_move -= (c[1] + g[2] + b[3]);
            else if (s == "GBC") current_move -= (g[1] + b[2] + c[3]);
            else if (s == "GCB") current_move -= (g[1] + c[2] + b[3]);

            // 如果是第一組，或者找到更小的搬移步數，則更新答案
            if (min_move == -1 || current_move < min_move) {
                min_move = current_move;
                best_config = s;
            }
        }

        cout << best_config << " " << min_move << endl;
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(1)$。對於每一組輸入，程式固定只會執行 6 次迴圈進行加減法配對，與輸入的數據規模完全無關。因此時間複雜度為極致的常數時間 $O(1)$，在系統評測中穩定呈現 0 毫秒。
- **空間複雜度**：$O(1)$。僅使用了幾個固定大小的變數與陣列來儲存瓶子數量與配置字串，空間消耗極低。

---

## 心得與反思

- **反向思考簡化運算**：
  這題讓我學到「逆向思維」在簡化演算法邏輯時的妙用。一開始想這題，可能很容易陷入「如何把第 1 箱的 G 和 C 分別搬到第 2、3 箱」這種繁雜的個別排列思考。但只要把觀點切換成「總數扣掉不動的人」，主程式碼直接變成漂亮的 6 行條件式，不僅極難出錯，可讀性也大幅提升。

- **邊界條件與字典序的優雅處理**：
  在程式設計競賽中，處理「多重最優解時的順序要求」往往容易寫出冗長的 `if-else`。這題利用「預先將枚舉清單按字典序排好」，再搭配嚴格小於（`<`）的更新策略，非常優雅地用一行程式碼解決了潛在的同分排序問題，這種工程小技巧非常值得吸收與內化。
