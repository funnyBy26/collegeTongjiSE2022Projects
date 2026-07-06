/*----------------------------------------------
	name : 付宝莹
	ID : 2251654
	phone number:19145163653
	e-mail:987596476@qq.com
	last edit time: 2024.6.7
-----------------------------------------------*/
#include <iostream>
#include <vector>
using namespace std;
vector<int>flowerbed;

int getint(const int minNum, const int maxNum, const string errorTips)
{
    int retNum = INT_MIN;
    while (1) {
        cin >> retNum;
        if (cin.fail() || retNum < minNum || retNum > maxNum) {
            // 若输入变量类型不同或数字不在要求范围内
            cin.clear();
            cin.ignore(1024, '\n');                           // 清除缓存区
            cout << errorTips;
        }
        else
            break;
    }
    return retNum;
}

bool canPlaceFlowers(const int size,const int n) {
    int count = 0;
    int preTmp = 0;
    int nextTmp = 0;
    for (int i = 0; i < size; i++) {
        if (flowerbed[i] == 0) {
            if (i > 0)
                preTmp = flowerbed[i - 1];
            else
                preTmp = 0;
            if (i < size - 1)
                nextTmp = flowerbed[i + 1];
            else
                nextTmp = 0;

            if (preTmp == 0 && nextTmp == 0) {
                flowerbed[i] = 1;
                count += 1;
                if (count >= n)
                    return true;
            }
        }
    }
    return count >= n;
}

int main() {
    
    int size = 0;
    int tmpNum = 0;
    
    cout << "Please enter the size of flowerbed in the range of 1~20000.";
    size = getint(1, 20000, "the number entered is not in the range,please enter it again!");

    cout << "Please enter the case 0 or 1 as blank or flower in flowerbed." << endl;
    for (int i = 0; i < size; i++) {
        cin >> tmpNum;
        if (tmpNum != 0 && tmpNum != 1){
            cout << "cin error!" << endl;
            exit(-1);
        }
        flowerbed.push_back(tmpNum);
    }
    int n = 0;
    cout << "Please enter the number of flowers wanted to insert to the flowerbed." << endl;
    n = getint(0, size, "the number entered is not in the range,please enter it again!");
    
    if (canPlaceFlowers(size, n))
        cout << "true";
    else
        cout << "false";
    return 0;
}
