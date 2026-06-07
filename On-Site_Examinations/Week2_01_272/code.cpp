#include<iostream>
using namespace std;

int main() {
    char x;           // 一個字一個字讀進來
    bool open = true; // 用來記錄現在要印的是開頭還是結尾的引號

    while (cin.get(x)) { // 持續讀到檔案結束
        if (x == '"') {  // 遇到雙引號
            if (open) 
                cout << "``";   // 如果是開頭，就印兩個反引號
            else 
                cout << "''";   // 如果是結尾，就印兩個單引號
            open = !open;       // 換一下狀態，下次就反過來
        }
        else {
            cout << x;          // 不是引號就照原樣輸出
        }
    }
};
