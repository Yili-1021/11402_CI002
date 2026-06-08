# UVa 673 - Parentheses Balance

## 問題描述
判斷一個字串是否為「正確配對的括號字串」。  
字串只包含 `()` 和 `[]`，必須符合以下規則：
1. 空字串是正確的。
2. 如果 A 和 B 都正確，那 AB 也正確。
3. 如果 A 正確，那 `(A)` 和 `[A]` 也正確。

---

## 原本錯誤邏輯與程式

### 錯誤邏輯
- 在判斷 `)` 或 `]` 時，直接呼叫 `st.top()`，沒有先檢查 stack 是否為空。  
- 當字串開頭就是 `)` 或 `]`，stack 是空的，呼叫 `st.top()` 會造成 **記憶體區段錯誤 (SIGSEGV)**。  
- 判斷流程不完整，可能提前輸出錯誤結果。

### 錯誤程式
```cpp
#include<iostream>
#include<string>
#include<stack>
using namespace std;
int main(){
    int n;
    cin >>n;
    cin.ignore();
    while(n--){
        string s;
        getline(cin,s);
        stack<char> st;
        bool em = false;
        
        for(char c:s){
            if(c=='('||c=='['){
                st.push(c);
                em=true;
            }else if(c==')'&& st.top()=='('){ //  這裡直接呼叫 st.top()
                if(st.empty()) break;
                st.pop();
                em=true;
            }else if(c==']'&& st.top()=='['){ //  這裡也直接呼叫 st.top()
                if(st.empty()) break;
                st.pop();
                em=true;
            }else{
                break;
            }
        }
        if(st.empty()&&em) {cout << "Yes"<<endl;}
        else cout << "No"<<endl;
    }
}
```
# UVa 673 - Parentheses Balance

## 修正過的邏輯

1. 在使用 `st.top()` 前，必須先檢查 `st.empty()`。  
2. 如果 stack 為空或頂端不是對應的括號 → 判定錯誤，直接結束迴圈。  
3. 成功配對後才 `st.pop()` 移除頂端元素。  
4. 最後檢查 stack 是否為空，確保所有括號都配對完成。  

---

## 修正程式
```cpp
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();
    while (n--) {
        string s;
        getline(cin, s);
        stack<char> st;
        bool ok = true;

        for (char c : s) {
            if (c == '(' || c == '[') {
                st.push(c);
            } else if (c == ')') {
                if (st.empty() || st.top() != '(') { //  先檢查 st.empty()
                    ok = false;
                    break;
                }
                st.pop();
            } else if (c == ']') {
                if (st.empty() || st.top() != '[') { //  先檢查 st.empty()
                    ok = false;
                    break;
                }
                st.pop();
            }
        }

        if (!st.empty()) ok = false;
        cout << (ok ? "Yes" : "No") << endl;
    }
}
```
## 複雜度分析

- **時間複雜度**：O(L)，L 為字串長度（每個字元只處理一次）。  
- **空間複雜度**：O(L)，最壞情況下所有括號都壓入 stack。  

---

## 心得與反思

- 原本的程式雖然能處理部分情況，但在空 stack 呼叫 `top()` 時會崩潰。  
- 修正後的程式更安全，邏輯也更清晰。  
- 這題讓我學到：使用 stack 時一定要先檢查 `empty()`，避免存取錯誤。  
