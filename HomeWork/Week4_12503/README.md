# UVa 12503 - Robot Instructions

## Problem Description

一個機器人初始位於位置 0。你會收到一系列指令：
1. `LEFT`: 向左移動一單位（位置 -1）。
2. `RIGHT`: 向右移動一單位（位置 +1）。
3. `SAME AS i`: 執行與第 $i$ 條指令相同的動作。

請計算執行完所有n條指令後，機器人的最終位置。

🔗 **[Problem Link](https://zerojudge.tw/ShowProblem?problemid=e567)**

---

## Learning Objectives
**State Management**: 學習如何使用陣列記錄過去的狀態（指令歷史）。
**String Parsing**: 練習在 C++ 中處理多變的字串輸入（例如處理 `SAME AS` 後接的數字）。
**Simulation**: 按照題目要求一步步模擬機器人的移動。

---

## Solution Approach

### Algorithm Logic
由於 SAME AS i 指令會參考之前的動作，我們必須將每一動作的「結果」儲存起來。

1. **資料結構**：建立一個陣列 cmd[105]，用來儲存第 i 次指令實際產生的位移量（-1 或 1）。
2. **讀取輸入**：
   * 讀取指令字串 s。
   * 如果是 LEFT，cmd[i] = -1。
   * 如果是 RIGHT，cmd[i] = 1。
   * 如果是 SAME AS，則再讀入一個無意義字串（如 "AS"）與整數 k，並設定 cmd[i] = cmd[k]。
3. **更新位置**：每次得出 cmd[i] 後，將其累加至總位移變數 map。

### Key Insights
* 不需要重新解析第 k 條指令的文字，只需要存儲該指令最後代表的「方向數值」即可。 
* 注意題目中的 k 是從 1 開始計數的，因此陣列建議從索引 1 開始使用。

---

## Source Code
**[Code Link](https://github.com/Yili-1021/11402_CI002/blob/main/HomeWork/Week4_12503/code.cpp)**
```cpp
#include <iostream>
using namespace std;
int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int map = 0;// 機器人最終位置
		int cmd[105];// 記錄歷史位移

		for (int i = 1; i <= n; i++) {
			string s;
			cin >> s;
			if (s == "LEFT") {
				cmd[i] = -1;
			}
			else if (s == "RIGHT") {
				cmd[i] = 1;
			}
			else { // 處理 "SAME AS k"，這裡最好改成if (s == "SAME")
				string tmp;//把as讀掉
				int k;
				cin >> tmp >> k;
				cmd[i] = cmd[k];// 把數字讀進來，存進 index
			}
			map += cmd[i];
		}
		cout << map << endl;

	}

};
```

---

## Complexity Analysis


**Time Complexity** $O(T \times n)$  T 為測試資料組數，n 為每組指令數。每一條指令只需 O(1) 時間處理。 
**Space Complexity** $O(n)$  使用 cmd[105] 陣列儲存指令歷史，空間消耗隨指令數線性增加。 

---

## Notes & Reflection

* **Challenges**
  * **字串處理**：遇到 SAME AS i 時，一開始會忘記跳過中間的 "AS"。後來發現可以用一個臨時字串 tmp把它讀掉，再讀取後面的整數 k。
  * **陣列索引**：題目給的 k 是從 1 開始。

* **Improvement**
  * **狀態記憶**：不需要每次都回頭去找第 k條指令是什麼文字，直接在 cmd[i] 存入 1 或 -1。當 SAME AS k 發生時，直接執行 cmd[i] = cmd[k]，這種**「記憶化」**的思想讓程式碼非常簡潔。

* **What I Learned**
  * 學會了如何在 C++ 中靈活運用 cin >> s 來拆解不固定格式的輸入。
  * 練習了如何將「動作」抽象化為數值（1 與 -1），並透過陣列紀錄歷史狀態來簡化模擬邏輯。

---

