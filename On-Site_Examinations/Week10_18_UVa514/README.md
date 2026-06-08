# UVa 514 - Rails

## 題目描述
有一個只有單軌道的火車站。  
火車從方向 A 進站，車廂編號依序為 `1, 2, ..., N`。  
它要從方向 B 出站，但出站順序可以改變。  
你要判斷：能不能用「進站暫存、再出站」的方式，讓火車在 B 的順序符合題目給的排列。

---

## 原本錯誤邏輯與程式碼

### 錯誤邏輯
- 嘗試用 `stack<int>` 存整個輸入數字，但沒有正確模擬「依序進站、暫存、出站」的過程。  
- 使用 `if (f = n)` → 這是賦值，不是比較，導致邏輯錯誤。  
- 沒有正確處理「外層 while 控制多組測資」與「內層 while 控制排列」的結構。  
- 判斷是否能完成排列的方式錯誤，導致輸出不符合題目要求。

### 錯誤程式碼
```cpp
#include<iostream>
#include<stack>
#include<string>
using namespace std;
int main(){
    int n;
    cin >> n;
    stack<int> train;
    while(true){
        int f;
        cin >> f;
        if(f==0) break;
        while(n--){
            bool em=false;
            if(f=n) { // ❌ 這裡是賦值，不是比較
                train.pop();
                em=true;
            }
            else {
                train.push(f);
                em=true;
            }
            if(train.empty()&&em){
                cout <<"Yes"<<endl;
            }else cout << "No"<<endl;
        }
    }
}
```
# UVa 514 - Rails

## 修正過的邏輯
1. **外層 while**：讀取 `n`，如果 `n == 0` → 整個程式結束。  
2. **內層 while**：讀取排列，如果第一個數字是 `0` → 結束這組 n 的測資。  
3. **模擬 stack**：
   - 從 1 開始依序 push 進 stack。  
   - 當 `stack.top() == 目標車廂` → pop。  
   - 如果最後能完全配對 → 輸出 `Yes`，否則 `No`。  

---

## 修正程式碼
```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) { // 外層：處理多組測資
        while (true) {      // 內層：處理每個排列
            int target[1000];
            cin >> target[0];
            if (target[0] == 0) break; // 結束這組 n 的排列
            for (int i = 1; i < n; i++) cin >> target[i];

            stack<int> st;
            int current = 1; // 目前進站的車廂編號
            bool ok = true;

            for (int i = 0; i < n; i++) {
                while (current <= target[i]) {
                    st.push(current++);
                }
                if (st.top() == target[i]) st.pop();
                else { ok = false; break; }
            }

            cout << (ok ? "Yes" : "No") << endl;
        }
        cout << endl; // 每組測資之間要空一行
    }
}
```
## 複雜度分析
- **時間複雜度**：O(N)，每個車廂最多 push / pop 一次。  
- **空間複雜度**：O(N)，最壞情況下所有車廂都暫存在 stack。  

---

## 心得與反思
- 原本的程式沒有正確模擬 stack 的行為，導致判斷錯誤。  
- 修正後的程式結構清楚：外層 while 控制整體，內層 while 控制排列，stack 模擬判斷順序。  
- 這題讓我更熟悉了 stack 的基本操作：`push()`、`pop()`、`top()`、`empty()`。  
- 也提醒我：寫程式時要注意「賦值」與「比較」的差別，避免邏輯錯誤。  
