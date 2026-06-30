# UVa 10189 - Minesweeper

## 問題描述
踩地雷（Minesweeper）是一款經典的電腦遊戲。給定一個 $n \times m$ 的網格，網格中有些格子藏有地雷（以字符 `*` 表示），有些格子則是安全的（以字符 `.` 表示）。

你的任務是將所有安全格子（`.`）替換為一個數字，該數字代表**與該格子相鄰的 8 個方向中，總共包含幾顆地雷**。

---

## 解題邏輯與程式

### 核心邏輯
這是一題經典的**二維陣列（Matrix）分量走訪**題目。我們不需要複雜的演算法，只需要精準地處理邊界與方向計數：

1. **建立地圖**：使用二維 `char` 陣列或 `vector<string>` 讀入地雷區。
2. **方向陣列**：定義兩個大小為 8 的一維陣列 `dx[]` 和 `dy[]`，分別代表周圍 8 個方向的橫向與縱向偏移量。這樣可以用一個簡單的 `for` 迴圈內嵌走訪周圍鄰居，避免寫出 8 個冗長的 `if` 判斷式。
3. **邊界檢查（Boundary Check）**：在走訪鄰居時，必須確保計算的座標 `(nx, ny)` 滿足 $0 \le nx < n$ 且 $0 \le ny < m$，防止存取到陣列邊界外的記憶體。
4. **輸出格式**：每組測資輸出前要加上 `Field #X:` 的標籤，並且**兩組測資之間必須要有一個空行**（最後一組測資後面不用多加空行），這點在 UVa 判題時非常嚴格。

### 完整程式碼
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 定義 8 個方向的偏移量
int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

int main() {
    int n, m, field_num = 1;
    bool first_field = true;

    while (cin >> n >> m && (n != 0 || m != 0)) {
        // 格式控制：除了第一個 Field 之外，其餘 Field 輸出前都要多空一行
        if (!first_field) {
            cout << endl;
        }
        first_field = false;

        vector<string> grid(n);
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }

        cout << "Field #" << field_num++ << ":" << endl;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // 如果本身就是地雷，直接輸出 '*'
                if (grid[i][j] == '*') {
                    cout << '*';
                } else {
                    int mine_count = 0;
                    // 檢查周圍 8 個方向
                    for (int d = 0; d < 8; d++) {
                        int ni = i + dx[d];
                        int nj = j + dy[d];

                        // 邊界檢查與地雷判定
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            if (grid[ni][nj] == '*') {
                                mine_count++;
                            }
                        }
                    }
                    cout << mine_count;
                }
            }
            cout << endl;
        }
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(n \times m)$。我們需要遍歷每一個格子，而每個格子最多只需要固定檢查周圍 8 個鄰居（常數時間 $O(1)$），因此總時間與地圖大小成線性正比，效率極高。
- **空間複雜度**：$O(n \times m)$。主要消耗在儲存地圖網格的 `std::vector<string>` 空間。

---

## 心得與反思

- **方向陣列的優雅性**：
  在處理網格（Grid）類型的題目時，手寫 8 個獨立的 `if` 判斷式不僅程式碼看起來混亂，也極其容易在複製貼上時漏改變數。引入 `dx[]` 和 `dy[]` 方向陣列配合迴圈，是撰寫二維地圖走訪（如 BFS、DFS 或周圍計數）時必備的優雅技巧。

- **嚴格的 Presentation Error 防禦**：
  這題最常讓人吃「PE（格式錯誤）」的地方就是換行控制。利用一個布林變數 `first_field` 來控制「非第一組測資前才輸出換行」，是處理競賽程式中「兩兩之間有空行，最後一行不留空行」最安全且乾淨的做法。
