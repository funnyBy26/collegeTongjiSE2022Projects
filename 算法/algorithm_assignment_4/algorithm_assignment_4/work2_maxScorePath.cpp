/*----------------------------------------------
	name : 付宝莹
	ID : 2251654
	phone number:19145163653
	e-mail:987596476@qq.com
	last edit time: 2024.6.7
-----------------------------------------------*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
const int maxLength = 1e5;
const int maxNum = 1e7;

vector<int>nums1;
vector<int>nums2;

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
int maxSum() {
    int nsize1 = nums1.size();
    int nsize2 = nums2.size();
    vector<long long>dpNums1(nsize1 + 1, 0), dpNums2(nsize2 + 1, 0);
    int i = nsize1 - 1;
    int j = nsize2 - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            dpNums1[i] = nums1[i] + dpNums1[i + 1];
            i--;
        }
        else if (nums1[i] < nums2[j]) {
            dpNums2[j] = nums2[j] + dpNums2[j + 1];
            j--;
        }
        else {
            long long sumValue = nums1[i] + max(dpNums1[i + 1], dpNums2[j + 1]);
            dpNums1[i] = dpNums2[j] = sumValue;
            i--;
            j--;
        }   
    }
    while (i >= 0) {
        dpNums1[i] = nums1[i] + dpNums1[i + 1];
        i--;
    }
    while (j >= 0) {
        dpNums2[j] = nums2[j] + dpNums2[ j+ 1];
        j--;
    }

    return (max(dpNums1[0], dpNums2[0]) % MOD);
}
int main() {
    int size1 = 0;
    int size2 = 0;
    int tmpNum = 0;

    cout << "Please enter the size of nums1 in the range of 1~1e5."<<endl;
    size1 = getint(1, 100000, "the number entered is not in the range,please enter it again!");

    cout << "Please enter the number in the range of 1~1e7." << endl;
    for (int i = 0; i < size1; i++) {
        cin >> tmpNum;
        if (tmpNum <1  && tmpNum >maxNum) {
            cout << "cin error!" << endl;
            exit(-1);
        }
        nums1.push_back(tmpNum);
    }
    cout << "Please enter the size of nums2 in the range of 1~1e5."<<endl;
    size2 = getint(1, 10000, "the number entered is not in the range,please enter it again!");

    cout << "Please enter the number in the range of 1~1e7." << endl;
    for (int i = 0; i < size2; i++) {
        cin >> tmpNum;
        if (tmpNum <1 && tmpNum >maxNum) {
            cout << "cin error!" << endl;
            exit(-1);
        }
        nums2.push_back(tmpNum);
    }
    cout << maxSum() << endl;
	return 0;
}