# UVa 11349 - Symmetric Matrix

## 問題描述
給定一個 $N \times N$ 的二維矩陣，請判斷它是否為「對稱矩陣（Symmetric Matrix）」。
根據題目定義，一個矩陣要符合對稱，必須同時滿足以下兩個條件：
1. 矩陣中的所有元素都必須**大於或等於 0**（非負整數）。
2. 矩陣以中心點為基準，旋轉 180 度後與原矩陣完全相同。換句話說，對於所有的 $i$ 和 $j$，都必須滿足 $M[i][j] == M[N - 1 - i][N - 1 - j]$。

---

## 解題邏輯與程式

### 核心邏輯
1. **處理輸入格式**：這題的輸入含有非數字字元（例如 `N = 3`），需要先用 `char` 讀取掉 `N` 和 `=`，再讀取矩陣的大小 $N$。
2. **資料型態選擇**：題目說明矩陣元素的數值可能非常大，使用一般的 32 位元整數（`int`）可能會發生溢位。因此，儲存矩陣時必須使用 64 位元整數（`long long`）。
3. **對稱性檢查**：
   - 在讀取資料時，如果發現任何小於 0 的數值，可以直接標記為不對稱。
   - 讀取完畢後，使用雙層迴圈遍歷矩陣的每一項，檢查 $M[i][j]$ 是否等於其對稱點 $M[N - 1 - i][N - 1 - j]$。只要有任何一項不相等，即可判定為不對稱並提前結束檢查。

### 完整程式碼
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t, case_num = 1;
    if (cin >> t) {
        while (t--) {
            char dummy1, dummy2; // 用來吃掉 "N" 和 "="
            int n;
            cin >> dummy1 >> dummy2 >> n;

            // 使用 long long 防止數值過大溢位
            vector<vector<long long>> matrix(n, vector<long long>(n));
            bool is_symmetric = true;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cin >> matrix[i][j];
                    // 條件 1：所有元素必須大於或等於 0
                    if (matrix[i][j] < 0) {
                        is_symmetric = false;
                    }
                }
            }

            // 條件 2：檢查中心對稱性 M[i][j] == M[n - 1 - i][n - 1 - j]
            if (is_symmetric) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (matrix[i][j] != matrix[n - 1 - i][n - 1 - j]) {
                            is_symmetric = false;
                            break;
                        }
                    }
                    if (!is_symmetric) break;
                }
            }

            if (is_symmetric) {
                cout << "Test #" << case_num++ << ": Symmetric." << endl;
            } else {
                cout << "Test #" << case_num++ << ": Non-symmetric." << endl;
            }
        }
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(N^2)$。對於每個測試案例，我們需要讀取並遍歷一個 $N \times N$ 的矩陣。矩陣總共有 $N^2$ 個元素，每個元素只進行常數次的讀取與比對，因此時間複雜度與矩陣大小成線性正比。
- **空間複雜度**：$O(N^2)$。主要消耗在配置二維 `std::vector` 來儲存整個 $N \times N$ 矩陣的空間。

---

## 心得與反思

- **魔鬼藏在細節裡（資料型態與負數）**：
  這題是非常經典的「看清題目限制」題。很多人（包括我自己）一開始看到「對稱」，就會直覺地只去檢查兩點是否相等，卻忽略了題目規定的「所有元素必須非負（$\ge 0$）」。再加上沒注意到隱藏的大數測資而用了 `int`，這兩個小地方非常容易讓人吃下冤枉的 WA（Wrong Answer）。

- **輸入緩衝區的處理技巧**：
  面對 `N = 3` 這種帶有雜質的輸入格式，不需要大費周章地用 `string` 讀入再切割。靈活利用多個 `cin >>` 配合 `char` 變數把前面的代號與等號「吃掉」，直接精準定位到後面的整數，是既快速又不容易出錯的輸入處理小技巧。
