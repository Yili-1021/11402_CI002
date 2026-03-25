#include<iostream>
#include<string>
using namespace std;

int main() {
    string L[1000]; // 用來存每一行文字的陣列
    int m = 0;      // 記錄最長那一行的字數
    int c = 0;      // 記錄總共有幾行

    // 一直讀輸入直到沒有東西
    while (getline(cin, L[c])) {
        // 如果這一行比目前最長的還長，就更新 m
        if ((int)L[c].size() > m) {
            m = L[c].size();
        }
        c++; // 行數加一
    }

    // 這裡開始做「旋轉」的動作
    //從 0 到最長的字數
    for (int col = 0; col < m; col++) {
        // 從最後一行往上走
        for (int row = c - 1; row >= 0; row--) {
            // 如果這一行有這個位置的字，就印出來
            if (col < (int)L[row].size()) {
                cout << L[row][col];
            }
            // 如果沒有字，就補空格
            else {
                cout << " ";
            }
        }
        // 換行
        cout << endl;
    }

    return 0;
}
