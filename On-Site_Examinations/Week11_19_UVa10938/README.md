# UVa 10935 - Throwing cards away I

## 問題描述
桌上有 $n$ 張牌，牌面由上到下依序為 $1$ 到 $n$。只要桌上還有至少兩張牌，就重複執行以下操作：
1. 丟棄最上面的牌。
2. 將此時最上面的牌移到整疊牌的最底部。

請依序輸出被丟棄的牌的順序，以及最後剩下來的那張牌。

---

## 原本邏輯與程式

### 原本邏輯
- 雖然題目概念是先進先出（FIFO）的佇列，但沒有直接使用 C++ STL 的 `queue`。
- 利用一個大小固定為 `1000` 的**陣列（Array）**，並搭配 `front` 與 `back` 兩個指標來手動模擬佇列的推入與彈出。
- 透過 `back - front > 1` 判斷牌組內是否還有至少兩張牌。
- 使用 `first` 布林變數來控制丟棄卡片時的逗號（`,`）格式輸出。

### 原本程式
```cpp
#include <iostream>
using namespace std;
int main()
{
	int n;
	while (cin >> n && n) {
		int q[1000];
		for (int i = 0; i < n; i++)q[i] = i + 1;
		cout << "Discarded cards:";
		int front = 0;
		int back = n;
		bool first = true;

		while (back - front > 1) {
			if (!first)cout << ",";
			cout << " " << q[front];
			first = false;
			front++;
			q[back] = q[front];
			back++;
			front++;
		}
		cout << endl<<"Remaining card: " << q[front] << endl;
	}
}
```
## 可以改進的部分

1. **陣列大小的潛在風險**：
   原始程式中陣列大小固定宣告為 `q[1000]`。每輪操作會將一張牌放到陣列尾端，總共大約會進行 $n-1$ 次移動，因此空間消耗大約是 $2n$。雖然這題測資限制 $n \le 50$ 絕對安全，但若遇到更大的測資，固定大小的陣列容易導致 **Buffer Overflow (陣列越界)**。
2. **記憶體利用率**：
   使用線性陣列模擬時，已經出隊的空間（`front` 之前的空間）就無法再被利用，會造成空間閒置。改用 C++ 標準函式庫的 `std::queue` 或使用環狀佇列（Circular Queue）可以更優雅、更安全地管理記憶體。
3. **語意清晰度**：
   手動操作 `front++` 與 `back++` 雖然效能好，但程式碼較不容易一眼看出行為邏輯。改用 `std::queue` 的 `push()` 與 `pop()` 能讓程式碼直接對應題目的「丟牌」與「放到牌底」敘述。

---

## 修正程式（使用 STL queue）

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            q.push(i);
        }

        cout << "Discarded cards:";
        bool first = true;

        // 當佇列中至少有兩張牌時繼續循環
        while (q.size() > 1) {
            if (!first) {
                cout << ",";
            }
            cout << " " << q.front(); // 輸出最上面的牌
            q.pop();                  // 丟棄最上面的牌
            first = false;

            q.push(q.front());        // 將現在最上面的牌放到最下面
            q.pop();                  // 移出頂端
        }

        cout << endl << "Remaining card: " << q.front() << endl;
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(n)$。每張牌最多被丟棄一次、移動一次，總共執行 $n-1$ 次操作，效率極高。
- **空間複雜度**：$O(n)$。無論是原本的陣列模擬還是 `std::queue`，最多同時儲存 $n$ 張（或陣列長度 $2n$）牌的空間。

---
## 心得與反思

- **從陣列模擬到標準容器的思維轉變**：
  這次寫題原本直覺地使用固定大小的陣列和雙指標（`front`/`back`）來手動模擬佇列（Queue）的行為。雖然在題目的小測資限制（$n \le 50$）下能夠順利通過，但也意識到手寫陣列容易留下 **Buffer Overflow（陣列越界）** 的隱患。
  
- **程式碼安全性與可讀性的提升**：
  改用 C++ STL 的 `std::queue` 後，不僅將記憶體管理的責任交給標準庫（自動動態配置大小，避免空間閒置與越界風險），更讓程式碼的語意直接對應題目的「丟牌（`pop`）」與「放回牌底（`push`）」。這讓我深刻體會到，善用標準容器能讓程式碼更精簡、更好維護，這也是未來寫更大規模專案或參加競賽時需要持續保持的良好習慣。
