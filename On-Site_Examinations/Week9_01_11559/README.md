# UVa 11559 - Event Planning

## 問題描述
有一群人要去參加活動，需要挑選飯店住宿。  
給定：
- N：參加人數  
- B：總預算  
- H：飯店數量  
- W：週末數量  

每間飯店提供：
- 每人費用 `price`  
- 每個週末可提供的床位數  

目標：找出能容納所有人且總花費不超過預算的最便宜方案。  
若無符合條件的飯店，輸出 `"stay home"`。

---

## 我的原始程式碼（錯誤版）
```cpp
#include <iostream>
#include<vector>
using namespace std;
int main()
{
    int p, b, h, w;
    cin >> p >> b >> h >> w;
    int cost;
    int ok = 0;
    while (h--) {
        cin >> cost;
        vector<int>wv(w);
        for (int i = 0;i < w;i++) {
            cin >> wv[i];
            if (wv[i] >= p&&p*cost<=b) ok++;
        }
    }
    if (ok > 0) {     //其中一周符合預算與人數
        cout << cost * p << endl;
    }
    else { cout << "stay home" << endl; }
}
```
---

## 我做錯的邏輯
- **只輸出最後一間飯店的價格**：  
  我在迴圈外輸出 `cost * p`，這樣只會印出最後一間飯店的結果，而不是最便宜的。  

- **判斷條件錯誤**：  
  我用 `ok > 0` 來判斷，但 `ok` 是符合條件的週末數量，並不代表最便宜的方案。  

- **沒有記錄最小花費**：  
  題目要求找出「最便宜的總花費」，但我沒有用變數追蹤最小值。
---

## 正確的邏輯
1. 宣告 `minCost`，初始值設成比預算大的數字。  
2. 每間飯店：
   - 讀入每人費用 `price`  
   - 讀入每個週末床位數  
   - 若床位 ≥ 人數，計算總花費 `total = n * price`  
   - 若 `total <= B`，更新 `minCost = min(minCost, total)`  
3. 最後：
   - 若 `minCost <= B` → 輸出 `minCost`  
   - 否則 → 輸出 `"stay home"`    
---

## 修正後的程式碼（正確版）
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, b, h, w;
    while (cin >> n >> b >> h >> w) {
        int minCost = b + 1; // 初始值設比預算大
        for (int i = 0; i < h; i++) {
            int price;
            cin >> price;
            vector<int> beds(w);
            for (int j = 0; j < w; j++) {
                cin >> beds[j];
                if (beds[j] >= n) { // 床位夠
                    int total = n * price;
                    if (total <= b) minCost = min(minCost, total);
                }
            }
        }
        if (minCost <= b) cout << minCost << endl;
        else cout << "stay home" << endl;
    }
    return 0;
}
```
---
## 複雜度分析

### 錯誤版邏輯
- **時間複雜度**：O(H × W)，但沒有正確追蹤最小值，輸出結果錯誤。  
- **空間複雜度**：O(W)，每次存放週末床位。  

### 修正版邏輯
- **時間複雜度**：O(H × W)，需要檢查每間飯店的每個週末。  
- **空間複雜度**：O(W)，用來存放每間飯店的床位數。  
- **正確性**：透過 `minCost` 變數追蹤最小花費，能正確輸出最便宜的方案。  
