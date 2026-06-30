# UVa 495 - Fibonacci Freeze

## 問題描述
題目要求非常單純：給定一個整數 $N$，請輸出第 $N$ 項費氏數列（Fibonacci number）的數值。
費氏數列的定義如下：
- $f(0) = 0$
- $f(1) = 1$
- $f(n) = f(n-1) + f(n-2)$ （當 $n \ge 2$）

---

## 解題邏輯與程式

### 核心邏輯
本題看似是基礎的遞迴或動態規劃，但有兩個關鍵點需要處理：

1. **大數運算（Big Integer）**：
   題目規定的 $N$ 最大可達 $5000$。費氏數列的增長速度極快，第 93 項就已經超出了 64 位元有號整數 `long long` 的最大範圍（約 $9 \times 10^{18}$）。當 $N = 5000$ 時，答案會是一個高達 1000 多位的超大整數。因此，我們必須使用字串（`std::string`）來實作**大數加法**。

2. **預處理建表（Bottom-up DP）**：
   由於有多組測試資料，若每次收到詢問才重新計算大數加法，會大幅浪費時間並導致超時（TLE）。最有效率的做法是在程式一開始，直接用一個迴圈把 $0$ 到 $5000$ 的費氏數列全部計算完並儲存進陣列（或 `vector`）中。後續每組詢問只需 $O(1)$ 時間查表輸出即可。

### 完整程式碼
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 實作大數加法：c = a + b
string add(const string& a, const string& b) {
    string res = "";
    int i = a.length() - 1;
    int j = b.length() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 10;
        res += to_string(sum % 10);
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    // 最佳化輸入輸出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 預處理建表，上限 N = 5000
    vector<string> fib(5001);
    fib[0] = "0";
    fib[1] = "1";

    for (int i = 2; i <= 5000; i++) {
        fib[i] = add(fib[i - 1], fib[i - 2]);
    }

    int n;
    // 2. $O(1)$ 時間查表回應詢問
    while (cin >> n) {
        cout << "The Fibonacci number for " << n << " is " << fib[n] << "\n";
    }

    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(N^2)$。預處理建表需要計算 $N = 5000$ 個狀態。由於每個狀態涉及大數加法，而大數的字串長度與 $N$ 呈線性關係（$f(5000)$ 約為 1048 位數），故單次加法平均耗時 $O(N)$。總建表時間為 $O(N^2)$。建表完成後，每組測試資料的查表與輸出時間為 $O(1)$。整體可在時限內高效通過。
- **空間複雜度**：$O(N^2)$。我們維護了一個大小為 $5001$ 的 `std::vector<string>` 表格，其中最長的字串長度約為 1050 個字元。總記憶體消耗大約在數個 MB 左右，遠低於評測系統限制。

---

## 心得與反思

- **大數規模的精準感度**：
  這題是驗證老手與新手對「型態邊界」敏感度的經典題。看到費氏數列，腦中就要自動跳出「$N=47$ 爆 `int`、$N=93$ 爆 `long long`」的常識。而當看到題目給到 $N=5000$ 時，不用懷疑，直接熟練地掏出字串大數加法模版才是唯一的生路。

- **I/O 速度優化的細節**：
  由於本題的輸出字串非常長（可達 1000 多位），且測試案例數量可能很大，頻繁使用 `std::endl` 會不斷重整快取區（buffer），導致顯著的 I/O 延遲。改用 `'\n'` 並加上 `ios_base::sync_with_stdio(false)` 進行解綁，是確保大數輸出題型不會卡在 I/O 關鍵點的必備競賽技巧。
