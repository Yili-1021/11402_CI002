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
