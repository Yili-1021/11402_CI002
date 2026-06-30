# UVa 11286 - Conformity

## 問題描述
某個大學裡有許多學生，每位學生這學期都需要選修 5 門課程。每位學生的選課組合（包含 5 個課程代號）代表了他的選課偏好。

大學裡最受歡迎的選課組合被定義為：「擁有最多學生選擇」的組合。現在給定所有學生的選課紀錄，請計算出**所有選修「最受歡迎組合」的學生總人數**。如果最受歡迎的組合不只一種（例如有三個組合並列第一，都有 10 個人選），則必須把這三個組合的人數加總（即輸出 30）。

---

## 解題邏輯與程式

### 核心邏輯
這題的核心在於**組合的統計與計數**。由於每位學生的 5 門課程在輸入時順序可能不同（例如學生 A 選 `100 200 300 400 500`，學生 B 選 `200 100 300 400 500`，本質上是同一種組合），因此必須先消除順序帶來的影響。

1. **標準化（Sorting）**：讀入每位學生的 5 門課程代號後，先將這 5 個數字由小到大排序。這樣一來，相同的選課組合就會擁有完全一致的排列順序。
2. **對應與計數（Map）**：排序後，我們可以將這 5 個數字轉化為一種方便比對的 key（例如直接存入 `std::vector<int>` 或拼成 `std::string`）。接著利用 C++ STL 的 `std::map`，將這個組合當作 key，出現次數當作 value 進行累加。
3. **找出最大值並加總**：
   - 遍歷一次 `map`，找出最高的人數紀錄（`max_popularity`）。
   - 再次遍歷 `map`，只要某個組合的選修人數等於 `max_popularity`，就把該人數累加到最終答案中。

### 完整程式碼
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        // 使用 map 來統計每種選課組合出現的次數
        map<vector<int>, int> popularity_map;
        int max_popularity = 0;

        for (int i = 0; i < n; i++) {
            vector<int> courses(5);
            for (int j = 0; j < 5; j++) {
                cin >> courses[j];
            }

            // 1. 排序 5 門課程，消除輸入順序的差異
            sort(courses.begin(), courses.end());

            // 2. 將組合計數加 1，並同步更新最高人氣紀錄
            popularity_map[courses]++;
            max_popularity = max(max_popularity, popularity_map[courses]);
        }

        // 3. 計算所有達到最高人氣組合的學生總人數
        int total_students = 0;
        for (auto const& [combination, count] : popularity_map) {
            if (count == max_popularity) {
                total_students += count;
            }
        }

        cout << total_students << endl;
    }
    return 0;
}
```
## 複雜度分析

- **時間複雜度**：$O(N \log N)$。對於每個學生，排序 5 門課的時間為常數 $O(5 \log 5) = O(1)$。接著將組合插入或更新到 `std::map` 中，由於 `map` 底層是紅黑樹，每次操作耗時 $O(\log N)$（這裡比較兩個長度為 5 的 vector 耗時也是常數級別）。總計 $N$ 個學生共耗時 $O(N \log N)$。最後遍歷 `map` 耗時 $O(N)$。整體效率非常優異。
- **空間複雜度**：$O(N)$。主要空間消耗在 `std::map` 中儲存的相異選課組合與其次數，最壞情況下（所有學生的組合都不同）會儲存 $N$ 個鍵值對。

---

## 心得與反思

- **複合型態作為 Map 的 Key**：
  這題讓我學到 C++ STL 中 `std::vector` 或 `std::string` 這類複合容器，因為內部已經實作了小於運算子（`<`），所以可以直接拿來當作 `std::map` 的 key使用。這在處理「多欄位聯合唯一鍵」的統計問題時，省去了手寫雜湊函數（Hash Function）或比較邏輯的麻煩，程式碼變得非常精簡。

- **同分狀況的全面思考**：
  題目中的一個小陷阱是「最受歡迎的組合可能不只一種」。如果在第一階段找出最大值後，就直覺地認為答案只要輸出 `max_popularity`，就會在有多個組合並列第一時拿到 WA。透過最後再跑一次迴圈將所有「並列第一」的人數統統加總，才算是把邊界狀況考慮完整。
