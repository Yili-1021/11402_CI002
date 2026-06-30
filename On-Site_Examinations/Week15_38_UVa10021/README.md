# UVa 10020 - Minimal Coverage

## 問題描述
給定一個線段的目標區間 $[0, M]$，以及許多長短不一的線段 $[L_i, R_i]$。
請從這些給定的線段中，挑選出**數量最少**的線段，使得它們的聯集能夠**完全覆蓋**目標區間 $[0, M]$。

如果不管怎麼組合都無法完全覆蓋區間 $[0, M]$，則輸出 `0`。

---

## 解題邏輯與程式

### 核心邏輯
這是一題非常經典的區間覆蓋問題，最適合使用**貪婪演算法（Greedy Algorithm）**來求解。

為了有效且最省線段地由左向右推進，我們可以採取以下策略：
1. **排序**：先將所有線段依照左端點（$L$）由小到大排序。如果左端點相同，則依照右端點（$R$）由大到小排序。
2. **貪婪挑選**：
   - 我們維護一個當前需要被覆蓋的左邊界 `current_left`，初始值為 `0`。
   - 在所有「左端點小於或等於 `current_left`」的可用線段中，**貪婪地挑選出右端點（$R$）最大的那一個線段**。因為這樣可以讓我們向右延伸得最遠，最快達到目標。
3. **推進與更新**：
   - 找到這個延伸最遠的線段後，將 `current_left` 更新為該線段的右端點，並將這條線段收入答案中。
   - 重複這個過程，直到 `current_left` 已經大於或等於 $M$（代表完全覆蓋），或者發現沒有任何線段的左端點能接到目前的邊界（代表出現斷層，無法完全覆蓋）。



### 完整程式碼
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Segment {
    int l, r;
};

// 排序比較函式：優先按左端點由小到大排序
bool compareSegments(const Segment& a, const Segment& b) {
    return a.l < b.l;
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int m;
            cin >> m;

            vector<Segment> segments;
            int l, r;
            while (cin >> l >> r && (l != 0 || r != 0)) {
                segments.push_back({l, r});
            }

            // 1. 依照左端點排序
            sort(segments.begin(), segments.end(), compareSegments);

            vector<Segment> ans;
            int current_left = 0; // 當前需要被覆蓋的左界
            size_t i = 0;
            bool possible = true;

            // 2. 貪婪掃描區間
            while (current_left < m) {
                int max_r = current_left;
                int best_idx = -1;

                // 尋找所有左端點符合要求、且右端點能延伸最遠的線段
                while (i < segments.size() && segments[i].l <= current_left) {
                    if (segments[i].r > max_r) {
                        max_r = segments[i].r;
                        best_idx = i;
                    }
                    i++;
                }

                // 如果找不到任何可以往右延伸的線段，代表無法完全覆蓋
                if (best_idx == -1) {
                    possible = false;
                    break;
                }

                // 採用該線段，並更新目前覆蓋的左界
                ans.push_back(segments[best_idx]);
                current_left = max_r;
            }

            // 3. 輸出結果
            if (possible && current_left >= m) {
                cout << ans.size() << endl;
                for (const auto& seg : ans) {
                    cout << seg.l << " " << seg.r << endl;
                }
            } else {
                cout << 0 << endl;
            }

            if (t > 0) cout << endl; // 測資間需輸出空行
        }
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(N \log N)$。其中 $N$ 為輸入的線段總數。最主要的耗時在於對所有線段進行排序（$O(N \log N)$）。隨後的貪婪選擇階段，我們使用了雙層迴圈的雙指針概念，每個線段最多只會被外層或內層迴圈存取一次，因此線性掃描的時間為 $O(N)$。總時間複雜度由排序決定。
- **空間複雜度**：$O(N)$。主要消耗在儲存所有線段的 `std::vector`，以及暫存答案線段的空間。

---

## 心得與反思

- **貪婪決策的目光放遠**：
  這題的貪婪思維非常精妙：既然我們要用「最少」的數量走到終點，那麼在起點（或當前安全區內）出發的所有人中，我們當然要挑「手伸得最長、能摸到最遠右方」的那個人。這種「守住左界，極大化右界」的策略是解決所有區間覆蓋題目的標準不二法門。

- **雙指針優化避免重複掃描**：
  在內層迴圈尋找 `segments[i].l <= current_left` 時，因為陣列已經排好序，我們可以用一個全域指針 `i` 一路往右走而不必每次都從頭（`i = 0`）開始找。這確保了每個元素只被看過一次，將時間複雜度穩穩壓在 $O(N)$ 的掃描效率，避開了暴力尋找可能導致的 $O(N^2)$ 危機。
