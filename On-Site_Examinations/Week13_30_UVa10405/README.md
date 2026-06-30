# UVa 10405 - Longest Common Subsequence

## 問題描述
給定兩個字串 $A$ 與 $B$，請計算出它們的**最長共同子序列（Longest Common Subsequence, LCS）**的長度。

所謂「子序列（Subsequence）」是指從原字串中刪除零個或多個字元後，其餘字元在**不改變相對順序**的情況下所組合而成的新字串（不要求在原字串中連續）。

---

## 解題邏輯與程式

### 核心邏輯
這是一題標準且極其經典的**動態規劃（Dynamic Programming, DP）**題目。我們可以使用一個二維陣列 `dp[i][j]` 來記錄狀態：



- **狀態定義**：`dp[i][j]` 表示字串 $A$ 的前 $i$ 個字元與字串 $B$ 的前 $j$ 個字元的最長共同子序列長度。
- **狀態轉移**：
  1. 如果當前字元相同（`A[i-1] == B[j-1]`）：代表這個字元可以納入共同子序列中，狀態由左上方轉移過來，即 `dp[i][j] = dp[i-1][j-1] + 1`。
  2. 如果當前字元不同（`A[i-1] != B[j-1]`）：代表這兩個字元至少有一個不屬於當前的 LCS，此時應取「忽略 $A$ 的當前字元」或「忽略 $B$ 的當前字元」兩種情況的最大值，即 `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`。
- **邊界與初始條件**：當任一字串長度為 $0$ 時，LCS 長度必定為 $0$，故 `dp[i][0] = 0` 且 `dp[0][j] = 0`。

### 完整程式碼
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string a, b;
    // 題目會給定多組測資，使用 getline 讀取整行，直到檔案結束（EOF）
    while (getline(cin, a) && getline(cin, b)) {
        int len_a = a.length();
        int len_b = b.length();

        // 建立 (len_a + 1) x (len_b + 1) 的二維 DP 陣列，並初始化為 0
        vector<vector<int>> dp(len_a + 1, vector<int>(len_b + 1, 0));

        for (int i = 1; i <= len_a; i++) {
            for (int j = 1; j <= len_b; j++) {
                if (a[i - 1] == b[j - 1]) {
                    // 字元相同，LCS 長度加 1
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // 字元不同，取左邊或上邊的最大值
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // 右下角的值即為兩個完整字串的 LCS 長度
        cout << dp[len_a][len_b] << endl;
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(N \times M)$。其中 $N$ 和 $M$ 分別為兩個字串的長度。我們需要填滿一個 $N \times M$ 的狀態矩陣，每個狀態的轉移只需要 $O(1)$ 的常數時間。題目限制字串長度在 1000 以內，計算量最大約為 $10^6$，執行時間通常在 0 到 10 毫秒之內。
- **空間複雜度**：$O(N \times M)$。主要消耗在儲存二維動態規劃狀態的 `std::vector`。由於每次計算 `dp[i][j]` 只會用到第 `i` 列與第 `i-1` 列的資料，空間複雜度可以透過滾動陣列（Rolling Array）技術優化至 $O(\min(N, M))$。

---

## 心得與反思

- **動態規劃的經典示範**：
  這題是所有字串 DP 題目的基石。透過將大問題（兩個長字串的 LCS）拆解成小問題（字串前綴的 LCS），並利用矩陣記錄已經計算過的子問題解答，完美體現了動態規劃「空間換時間」的核心精神。

- **邊界與輸入的坑（getline 的必要性）**：
  這題在 UVa 中有個容易讓人吃 WA 的隱藏陷阱——**測資中可能包含空字串**。如果使用 `cin >> a >> b` 讀取，遇到空字串時會直接跳過並把下一行的字串讀進來，導致字串配對完全錯位。堅持使用 `getline(cin, s)` 來保留空行與空格，是處理競賽字串輸入時最穩健的良好習慣。
