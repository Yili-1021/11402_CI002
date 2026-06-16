# UVa 540 - Team Queue

## 問題描述
在一個排隊的情境中，有許多個團隊（Teams）。如果一個新來的人發現隊伍裡已經有自己的隊員，他就可以直接插隊到所有隊員的最尾端（即「排在最後一個隊員的後面」）；如果隊伍裡沒有任何隊員，他就只能乖乖排到整條大隊伍的最後面。

排隊系統支援以下三種指令：
1. `ENQUEUE x`：元素 $x$ 進入隊伍。
2. `DEQUEUE`：隊伍最前端的元素出隊並輸出。
3. `STOP`：結束當前測試資料。

---

## 邏輯與程式

### 邏輯
1. **利用「佇列的佇列（Queue of Queues）」簡化邏輯**：
   這題如果單純用一個 `std::queue` 或 `std::vector` 來強行插入元素，會面臨高昂的時間複雜度。最優雅且高效的改進方式是利用一個大佇列 `queue<int> team_q` 來維護「目前大隊伍裡有哪些團隊在排隊」，並搭配一個陣列或 Map 儲存每個團隊各自的小佇列 `queue<int> q[1000]`。
2. **快速查詢團隊所屬（Mapping）**：
   每當一個新成員要進隊時，我們需要快速知道他屬於哪一隊。可以使用一個大小足夠的陣列 `element_to_team[x]` 來當作查找表（查表時間 $O(1)$），迅速找出成員 $x$ 的所屬團隊編號。
3. **避免重複將團隊加入大佇列**：
   如果某個團隊的小佇列原本就是空的，代表大隊伍裡現在沒有該隊的成員，此時才需要把這個團隊編號 `push` 進大佇列。如果小佇列本來就有成員，直接將新成員推進該隊的小佇列即可，不需重複驚動大佇列。

### 程式
```cpp
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
using namespace std;

// 元素最大值通常在題目限制內，這裡假設元素編號小於 1000000
int element_to_team[1000000]; 

int main() {
    int t, scenario = 1;
    while (cin >> t && t) {
        cout << "Scenario #" << scenario++ << endl;

        // 讀取團隊資訊並建立查找表
        for (int i = 0; i < t; i++) {
            int n;
            cin >> n;
            for (int j = 0; j < n; j++) {
                int element;
                cin >> element;
                element_to_team[element] = i; // 記錄這個元素屬於第 i 隊
            }
        }

        queue<int> team_q;          // 大佇列：記錄目前有哪些團隊在排隊
        vector<queue<int>> q(t);    // 小佇列陣列：每個團隊各自的排隊佇列

        string cmd;
        while (cin >> cmd && cmd != "STOP") {
            if (cmd == "ENQUEUE") {
                int x;
                cin >> x;
                int team_id = element_to_team[x];

                // 如果該團隊的小佇列目前是空的，代表大隊伍中還沒有這個團隊
                if (q[team_id].empty()) {
                    team_q.push(team_id); // 將團隊編號加入大佇列中
                }
                q[team_id].push(x);       // 成員加入自己團隊的小佇列
            } 
            else if (cmd == "DEQUEUE") {
                int current_team = team_q.front(); // 找出目前大隊伍最前面的團隊
                cout << q[current_team].front() << endl; // 輸出該團隊最前面的成員
                q[current_team].pop();             // 移除該成員

                // 如果該團隊的所有成員都出隊了，大隊伍中就不再需要保留這個團隊
                if (q[current_team].empty()) {
                    team_q.pop();
                }
            }
        }
        cout << endl; // 每組測資輸出完後加一個空行
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：
  - **初始化**：$O(M)$，其中 $M$ 為所有團隊成員的總數，用於建立查找表。
  - **每筆指令（ENQUEUE / DEQUEUE）**：$O(1)$。得益於「大佇列包小佇列」與陣列查表的設計，每次插隊與出隊的操作都只需要常數時間。
- **空間複雜度**：$O(M)$。主要消耗在 `element_to_team` 查找表陣列，以及儲存佇列元素的空間。

---

## 心得與反思

- **從線性尋找到結構化設計的改進**：
  這題的精髓在於「插隊」的模擬。如果一開始只用單一線性容器（如 `vector` 或 `list`）去尋找同隊隊友並強行插入，會隨著隊伍拉長而導致嚴重的超時（TLE）。
  
- **複合容器的強大威力**：
  改進後的解法展示了「用結構解決演算法問題」的魅力。透過將 `queue` 嵌套進另一個 `queue`（大佇列管團隊，小佇列管隊員），把看似複雜的插隊規則轉化成標準佇列的常數時間操作。這種「拆解層級、分工合作」的容器設計思維，是提升程式碼效能與擴充性的關鍵。
