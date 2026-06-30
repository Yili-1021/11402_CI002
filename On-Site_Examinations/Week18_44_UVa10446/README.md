# UVa 10446 - The Marriage Interview

## 問題描述
題目給定了一段看似簡單的遞迴程式碼，用來計算某種類似費氏數列的變形。程式碼如下：

```cpp
long long trib(int n, int back) {
    long long sum = 0;
    int i;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    for (i = 1; i <= back; i++)
        sum += trib(n - i, back);
    return sum;
}
```
## 解題邏輯與程式

### 核心邏輯
如果直接照著題目給的程式碼進行純遞迴計算，當 $n$ 較大時，會因為大量重疊的子問題而導致時間超時（TLE）。因此，我們必須使用動態規劃（Dynamic Programming）的記憶化搜索或建表來解決。

我們可以用一個二維矩陣 `dp[n][back]` 來儲存「當參數為 `n` 且 `back` 為指定值時，函式被呼叫的總次數」：

- **基底條件（Base Cases）**：
  觀察原程式碼，當 $n \le 0$ 或 $n = 1$ 時，函式會直接執行 `return`，不會進入 `for` 迴圈。因此，不論 `back` 是多少，這些狀況下函式都只被呼叫了 1 次。
  - 當 $n \le 0$ 時，`dp[n][back] = 1`
  - 當 $n = 1$ 時，`dp[n][back] = 1`

- **狀態轉移公式**：
  當 $n > 1$ 時，呼叫一次 `trib(n, back)` 本身算作 1 次。接著它會經由 `for` 迴圈衍生出 `back` 次新的子呼叫。因此，總呼叫次數為「自身這 1 次」加上「所有子呼叫次數的總和」：
  $$\text{dp}[n][\text{back}] = 1 + \sum_{i=1}^{\text{back}} \text{dp}[n-i][\text{back}]$$
  > **注意**：如果 $n-i < 0$，在轉移時一律視為對應到 $n \le 0$ 的基底狀況（即呼叫次數為 1）。
  ### 完整程式碼

```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// 題目範圍：n <= 60, back <= 60
// 呼叫次數增長極快，必須使用 unsigned long long 來儲存以防溢位
unsigned long long dp[65][65];

unsigned long long solve_dp(int n, int back) {
    // 基底條件：n <= 0 或 n == 1，函式直接 return，只算呼叫 1 次
    if (n <= 0 || n == 1) return 1;
    
    // 如果已經計算過，直接回傳
    if (dp[n][back] != 0) return dp[n][back];

    unsigned long long sum = 1; // 算入目前自己被呼叫的這 1 次
    for (int i = 1; i <= back; i++) {
        sum += solve_dp(n - i, back);
    }

    return dp[n][back] = sum;
}

int main() {
    int n, back;
    int case_num = 1;
    
    // 初始化 DP 表格為 0
    memset(dp, 0, sizeof(dp));

    // 當輸入的 n 超過 60 時結束程式
    while (cin >> n >> back && n <= 60) {
        cout << "Case " << case_num++ << ": " << solve_dp(n, back) << endl;
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(N \cdot \text{back}^2)$。DP 的狀態總共有 $N \times \text{back}$ 個（此處上限為 $60 \times 60 = 3600$）。每個狀態在計算時，需要跑一個長度為 `back` 的 `for` 迴圈，因此總複雜度為 $O(N \cdot \text{back}^2)$。由於總計算量極小且具備記憶化優化，不論測資有多少，查表均可在 0 毫秒內瞬間完成。
- **空間複雜度**：$O(N \cdot \text{back})$。主要消耗在維護 $65 \times 65$ 的二維 `unsigned long long` 表格。

---

## 心得與反思

- **看清題目的真正核心**：
  這題最巧妙的盲點在於「程式碼的誤導」。第一眼看到題目給的 `trib` 函式，直覺會以為是要去優化並計算出這個數列的數值。但仔細讀題後才發現，題目真正要求的是**遞迴樹的節點總數（呼叫次數）**。在競賽中，確認「Goal（目標）」到底是什麼，比急著寫程式碼重要得多。

- **大數與溢位的潛在危機**：
  雖然題目給的 $N \le 60$ 看起來很小，但由於它是多叉樹（分支出去 `back` 個子節點）的指數級增長，總呼叫次數會膨脹得非常誇張，甚至會超越 64 位元有號整數（`long long`）的上限。選擇使用 `unsigned long long` 或是精準處理邊界，是這題能否順利拿到 AC 的關鍵細節。
