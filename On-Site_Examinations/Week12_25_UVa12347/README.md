# UVa 12347 - Binary Search Tree

## 問題描述
二元搜尋樹（Binary Search Tree, BST）是一種特殊的二元樹，它符合以下特性：
1. 左子樹的所有節點值都小於根節點值。
2. 右子樹的所有節點值都大於根節點值。
3. 左右子樹也分別為二元搜尋樹。

已知某一棵二元搜尋樹的**前序走訪（Pre-order Traversal）**結果，請利用這個結果重構該二元搜尋樹，並輸出其**後序走訪（Post-order Traversal）**的結果。

---

## 解題邏輯與程式

### 核心邏輯
前序走訪的順序為：**根節點 $\rightarrow$ 左子樹 $\rightarrow$ 右子樹**。
利用這個特性，我們不需要真的在記憶體中建立出整棵樹的指標結構，而是可以透過**分治法（Divide and Conquer）**配合遞迴來直接輸出後序結果（**左子樹 $\rightarrow$ 右子樹 $\rightarrow$ 根節點**）：

1. **確定根節點**：在前序序列中，當前範圍的第一個元素必定是該子樹的「根節點」。
2. **劃分左右子樹**：從第二個元素開始往後尋找，第一個「大於根節點」的元素位置，就是右子樹的起點。這個起點左邊的區段屬於左子樹，右邊（包含起點）的區段屬於右子樹。
3. **遞迴與輸出**：先遞迴處理左子樹區段，再遞迴處理右子樹區段，最後輸出當前的根節點，即可完美符合後序走訪的順序。

### 完整程式碼
```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> pre;

// lower 和 upper 代表當前子樹在前序陣列中的索引範圍 [lower, upper)
int solve(int lower, int upper) {
    if (lower >= upper) return 0;

    int root_val = pre[lower];
    int right_start = lower + 1;

    // 尋找第一個大於根節點的值，作為右子樹的起點
    while (right_start < upper && pre[right_start] < root_val) {
        right_start++;
    }

    // 遞迴處理左子樹：範圍為 [lower + 1, right_start)
    solve(lower + 1, right_start);
    
    // 遞迴處理右子樹：範圍為 [right_start, upper)
    solve(right_start, upper);

    // 後序走訪：最後輸出根節點
    cout << root_val << endl;
    return 0;
}

int main() {
    int val;
    // 題目沒有給定測資數量，讀取到檔案結束（EOF）為止
    while (cin >> val) {
        pre.push_back(val);
    }

    // 開始分治遞迴
    solve(0, pre.size());

    return 0;
}
```
## 複雜度分析

- **時間複雜度**：
  - **平均情況**：$O(N \log N)$。若二元搜尋樹相對平衡，每次劃分左右子樹大約能切成對半，遞迴深度為 $O(\log N)$。
  - **最壞情況**：$O(N^2)$。若樹退化成一條直線（例如輸入數據完全遞增或遞減），每次只能切出一個節點，此時複雜度會退化。但由於這題 $N \le 10000$，即使是最壞情況也能在時限內輕鬆通過。
- **空間複雜度**：$O(N)$。主要消耗在儲存前序走訪結果的 `std::vector`，以及遞迴時系統 stack 的空間。

---

## 心得與反思

- **走訪規律的逆向應用**：
  這題展示了二元搜尋樹與一般二元樹的不同之處。一般二元樹必須同時知道「前序+中序」或「後序+中序」才能唯一確定一棵樹；但二元搜尋樹因為具備「左小右大」的天然嚴格數學規律，光是憑藉「前序走訪」的資訊，就能直接在陣列中切分出左右子樹。
  
- **虛擬建樹的思想**：
  在解決樹狀結構問題時，能「不寫 `struct Node`、不手動 new 指標」就不要寫。直接利用陣列範圍（`lower`/`upper`）在遞迴中進行「虛擬建樹」，不僅程式碼乾淨、不易寫錯，效能與記憶體掌握度也更高。
