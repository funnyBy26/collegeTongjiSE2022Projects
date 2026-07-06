/*
  文件功能：实现一个算法搜索M*N矩阵中的一个目标值，矩阵每行元素从左到右升序，每列元素从上到下升序，时间复杂度为O(m+n)
  作者：付宝莹
  电话：19145163653
  电子邮件：2251654@tongji.edu.cn
  最新修改日期：2024/4/27
  版本：1.0
  说明：本代码输入处理部分援引自github上GyxPillar博主，仅用于非商业性用途，原博主提供完整的C++源代码，
        我出于自身需求对源代码行了部分修改
 */
#include <iostream>
#include <vector>
#include<cstring>
#include <iomanip>
using namespace std;

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

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty())
        return false;

    int rows = matrix.size();
    int cols = matrix[0].size();

    int nowRow = 0;
    int nowCol = cols - 1;

    while (nowRow < rows && nowCol >= 0) {
        if (matrix[nowRow][nowCol] == target)
            return true;
        else if (matrix[nowRow][nowCol] < target)
            nowRow++;
        else
            nowCol--;
    }

    return false;
}
int main()
{
    int m, n;//the number of rows and columns in the matrix
    cout << "Please enter the number of rows in the matrix(1~300)";
    m = getint(1, 300, "the number entered is not in the rang,please enter it again!");
    cout << "Please enter the number of columns in the matrix(1~300)";
    n = getint(1, 300, "the number entered is not in the rang,please enter it again!");
   
    //define a matrix size:m*n
    vector<vector<int>>matrix(m, vector<int>(n));

    cout << "Pleaase enter the elements of the matrix:" << endl;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = getint(INT_MIN, INT_MAX, "the number entered is not in the rang,please enter it again!");

    int target;
    cout << "Please enter the target value to search:";
    target = getint(INT_MIN, INT_MAX, "the number entered is not in the rang,please enter it again!");

    if (searchMatrix(matrix, target))//successfully searched the target in the matrix
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}