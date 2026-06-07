#include <iostream>
using namespace std;

int main() {
    int s, d;
    // 以用 while 讀到 EOF
    while (cin >> s >> d) {
        int sum = 0; // 累積入住人數
        // 從第 s 天開始，每天入住人數依序增加
        for (int day = s;; day++) {
            sum += day; // 累加當天入住人數
            if (sum >= d) {
                // 當累積人數達到或超過 d，輸出當天編號
                cout << day << endl;
                break; // 結束迴圈，處理下一筆測資
            }
        }
    }
    return 0;
}
