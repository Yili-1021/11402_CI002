# UVa 410 - Station Balance

## 問題描述
你有 $C$ 個離心機艙（Chambers）以及 $2C$ 個以內（設為 $S$ 個）的待測樣本（Specimens）。每個樣本都有各自的重量 $W_i$。每個艙室最多只能容納 **2 個** 樣本。

如果一個艙室內沒有放任何樣本，它的重量為 0；如果放了樣本，它的重量就是內部樣本的重量總和。
令所有樣本的平均重量為 $A = \frac{\sum W_i}{C}$。
我們的目標是將這 $S$ 個樣本分派到這 $C$ 個艙室中，使得各艙室重量與平均重量的**絕對不平衡度之和（Total Imbalance）達到最小**：
$$\text{Imbalance} = \sum_{i=1}^{C} |X_i - A|$$
其中 $X_i$ 為第 $i$ 個艙室的實際總重量。

請輸出每個艙室的分配情況（由小到大排列艙室編號，艙室內樣本重量也由小到大輸出），並輸出最終的最小不平衡度。

---

## 解題邏輯與程式

### 核心邏輯
這是一題非常精妙且經典的**貪婪演算法（Greedy Algorithm）**題目，通常被稱為「**貪婪配對策略（Greedy Pairing Strategy / Match Strategy）**」。

1. **補齊虛擬樣本**：
   題目規定艙室有 $C$ 個，最多能裝 $2C$ 個樣本，但實際樣本數 $S$ 可能小於 $2C$。為了讓配對邏輯完全一致，我們可以直接補上 $2C - S$ 個「重量為 0」的虛擬樣本。此時，總樣本數恰好被擴充為 $2C$ 個。
2. **排序**：
   將這 $2C$ 個樣本（包含補 0 的部分）依照重量由小到大排序。
3. **極端值配對（Greedy Pairing）**：
   將排序後的數列進行「首尾兩兩配對」：最輕的與最重的放同一個艙室，次輕的與次重的放同一個艙室。也就是第 $i$ 個艙室分配到的兩個樣本索引為 $i$ 與 $2C - 1 - i$。



透過這種大配小、小配大的對稱配對方式，在數學上可以證明它能最大程度地逼近平均數 $A$，進而使絕對差之和最小。

### 完整程式碼
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
    int c, s;
    int set_num = 1;
    while (cin >> c >> s) {
        vector<int> specimens(2 * c, 0); // 直接開 2C 大小，預設補 0
        double sum = 0;

        for (int i = 0; i < s; i++) {
            cin >> specimens[i];
            sum += specimens[i];
        }

        double avg = sum / c; // 計算平均值

        // 1. 進行排序（前 S 個是實體，後面 2C-S 個是 0，排序後 0 會跑到最前面）
        sort(specimens.begin(), specimens.end());

        cout << "Set #" << set_num++ << endl;

        double total_imbalance = 0;

        // 2. 進行首尾貪婪配對
        for (int i = 0; i < c; i++) {
            cout << " " << i << ":";
            
            int p1 = specimens[i];
            int p2 = specimens[2 * c - 1 - i];

            // 輸出時注意：虛擬的 0 不用印出來
            if (p1 != 0) cout << " " << p1;
            if (p2 != 0) cout << " " << p2;
            cout << endl;

            // 累加該艙室的不平衡度
            total_imbalance += abs((p1 + p2) - avg);
        }

        // 3. 輸出總不平衡度，保留 5 位小數
        cout << "IMBALANCE = " << fixed << setprecision(5) << total_imbalance << endl << endl;
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(C \log C)$。主要的效能瓶頸在於對大小為 $2C$ 的陣列進行排序，時間複雜度為 $O(2C \log(2C)) = O(C \log C)$。接下來的配對與計算不平衡度只需一個跑 $C$ 次的單層迴圈 $O(C)$。由於題目限制 $C \le 5$，這個計算量在 0 毫秒內就能瞬間執行完畢。
- **空間複雜度**：$O(C)$。使用了一個固定大小為 $2C$ 的 `std::vector` 來儲存所有樣本。

---

## 心得與反思

- **虛擬哨兵（補零）化繁為簡**：
  這題最漂亮的手法在於「補 0」。如果直接拿長度為 $S$ 的陣列去想怎麼分配，會因為「有些艙室裝 1 個、有些裝 2 個」而讓判斷式和邊界變得異常繁瑣。透過直接補 0 把問題全部強轉成「每個艙室一定要裝 2 個」，排序後 these 0 會自然歸位到最左側，完美的融入了首尾配對的邏輯中，這招真的非常高明！

- **貪婪配對的數學直覺**：
  本題是「排序不等式」與「平攤數值偏離度」的經典變形。當我們想讓一組組合的總和盡可能接近某個定值時，最有效率的方法就是讓極大值與極小值互補。藉由親手實作這題，能更深刻地體會到如何利用對稱性（`i` 與 `2*c - 1 - i`）在線性時間內完成最佳化配對。
