# UVa 11364 - Optimal Parking

## 問題描述
Michael 要去逛街，他的車可以停在 Long Street 上的任意整數位置。  
街上有幾家店，每家店的位置也是整數。  
他希望選一個停車位置，讓他走去所有店的總距離最短。  

最短距離的計算方式為：
> (最遠的店位置 − 最近的店位置) × 2

---

## 我的邏輯（原始程式）
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;
    while (n--) {
        int num;
        cin >> num;
        vector<int> map(num);
        for (int i = 0;i < num;i++) {
            cin >> map[i];
        }
        sort(map.begin(), map.end());
        int midmap = map[num - 1] - map[0];
        int total = midmap * 2;
        cout << total << endl;
    }
}
```
- **只輸出最後一間店的結果**：  
  一開始我用排序後的陣列，卻沒有正確理解，只是單純輸出最後一筆計算，沒有針對題目要求的「最遠與最近」來處理。  

- **沒有簡化計算**：  
  我原本以為要計算所有店的距離總和，結果程式碼變得複雜。其實只要找最大值與最小值即可。  

---
## 正確的邏輯
1. 讀入店的數量 `num`。  
2. 讀入所有店的位置。  
3. 找出最小值 `minVal` 和最大值 `maxVal`。  
4. 計算 `(maxVal - minVal) * 2`。  
5. 輸出結果。  

---

## 修正後的程式碼（正確版）
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> positions(n);
        for (int i = 0; i < n; i++) {
            cin >> positions[i];
        }
        sort(positions.begin(), positions.end());
        int total = (positions.back() - positions.front()) * 2;
        cout << total << endl;
    }
    return 0;
}
```
## 複雜度分析

### 我的邏輯
- **時間複雜度**：O(n log n)，因為用了 `sort()`。  
- **空間複雜度**：O(n)，存放所有店的位置。  

### 建議邏輯修正
- **時間複雜度**：O(n)，只需一次遍歷找最大值與最小值。  
- **空間複雜度**：O(1)，只需兩個變數追蹤最大值與最小值。  

---

## 心得與反思
- 我的程式雖然能過題目，但用了排序，效率不算最佳。  
- 建議邏輯更簡單，直接在輸入時更新最大值與最小值即可。  
- 這題提醒我：在寫程式前要先理解題目的數學邏輯，避免多餘的計算。  
