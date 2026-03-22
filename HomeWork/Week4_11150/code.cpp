#include <iostream>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int em = n;   // 當前空瓶數
        int tol = n;  // 總共喝掉的可樂數
        
        // 模擬正常兌換
        while (em >= 3) {
            int newcola = em / 3;
            tol += newcola;
            //更新手邊剩下的空瓶 新喝完的 + 剛才湊不滿 3 個留下的
            em = em % 3 + newcola;
        }
        
        // 處理借瓶子情況：剩 2 個可以借 1 個湊 3 個，喝完還 1 個
        if (em == 2) {
            tol++;
        }
        
        cout << tol << endl;
    }
    return 0;
}
