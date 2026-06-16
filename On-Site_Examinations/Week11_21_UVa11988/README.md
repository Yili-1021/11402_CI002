# UVa 11988 - Broken Keyboard (Beiju Text)

## 問題描述
你在打字時，鍵盤壞掉了，它會隨機自動按下 `[` (Home 鍵) 與 `]` (End 鍵)。
- 當按下 `[` 時，游標會跳到整行文字的最前端。
- 當按下 `]` 時，游標會跳到整行文字的最後端。

輸入一個包含 `[`、`]` 與英文字母的字串，請輸出最後在螢幕上呈現的文字順序。

---

## 原本邏輯與程式

### 原本邏輯
- 使用兩個 `string` 變數：`a` 儲存目前已確定的主字串，`t` 儲存目前正在輸入的暫存片段。
- 利用布林變數 `front` 記錄當前游標是否在行首。
- 當遇到 `[` 或 `]` 時，將暫存片段 `t` 串接到 `a` 的前方，並清空 `t`、切換狀態。
- 逐字元處理，試圖用字串拼接模擬游標移動。

### 原本程式
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        string a = "";
        string t = "";
        bool front = false;
        for (char c : s) {
            if (c == '[') {
                a = t + a;
                t = "";
                front = true;
            }
            else if (c == ']') {
                a = t + a;
                t = "";
                front = false;
            }
            else {
                if (front) t += c;
                else a = t + a; // 這裡每次字元輸入都進行字串拼接
            }
        }
        cout << a << endl;
    }
    return 0;
}
```
## 可以改進的部分

1. **字串拼接帶來的 TLE 風險**：
   在原本的程式中，不論是 `a = t + a` 還是逐字元拼接，C++ 在執行 `string` 的前方插入時，都必須把後面的所有字元往後移，時間複雜度為 $O(N)$。在整筆字串長度達 $10^5$ 的情況下，整體複雜度會退化到 $O(N^2)$，導致 **TLE (超時)**。
2. **善用雙向佇列（std::list）與迭代器（Iterator）**：
   這題本質上是「鏈結串列（Linked List）」的完美範例。C++ 的 `std::list` 底層是雙向鏈結串列，在任意位置插入元素只需要 $O(1)$ 的時間。配合迭代器模擬「游標」，遇到 `[` 就將游標移到 `list.begin()`，遇到 `]` 就移到 `list.end()`，一般字元就直接在游標處插入，效率會大幅提升。

---

## 修正程式（使用 std::list 優化）

```cpp
#include <iostream>
#include <string>
#include <list>
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        list<char> text;
        // 建立一個迭代器（游標），初始指向 list 的尾端
        list<char>::iterator it = text.end();

        for (char c : s) {
            if (c == '[') {
                it = text.begin(); // 游標跳到行首
            } 
            else if (c == ']') {
                it = text.end();   // 游標跳到行尾
            } 
            else {
                // 在游標所在位置插入字元，insert 後迭代器會自動指向新插入元素的下一個位置
                text.insert(it, c);
            }
        }

        // 依序輸出 list 中的字元
        for (char c : text) {
            cout << c;
        }
        cout << endl;
    }
    return 0;
}
```
## 心得與反思

- **時間複雜度的陷阱**：
  原本的想法在邏輯上非常直觀，試圖用局部字串拼接來解決問題。這讓我想起在練習演算法時，不能只追求「功能正確」，必須時刻注意背後資料結構的實作原理（例如 `string` 前方插入的代價）。
  
- **精準選用資料結構**：
  這題讓我深刻體會到 `std::list` 的威力。以前覺得 `std::vector` 或 `std::string` 很好用，但遇到「頻繁在中間或前端插入元素」的情境時，鏈結串列（Linked List）那 $O(1)$ 的插入特性才是標準解法。利用迭代器當作「螢幕上的游標」，讓程式碼的語意跟題目敘述完美契合，是非常漂亮的思想轉變。
