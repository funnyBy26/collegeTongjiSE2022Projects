/*----------------------------------------------
name : ¸¶±¦Ó¨
ID : 2251654
phone number:19145163653
e-mail:987596476@qq.com
last edit time: 2024.5.22
-----------------------------------------------*/
#include <iostream>
#include <vector>
using namespace std;

/**********************************************************
* function name: countPaths
* type of ret: int
* function: using to count the number of paths to get to the destination
**********************************************************/
int countPaths(int row, int column) {
    vector<vector<int>> dp(row, vector<int>(column, 1));
    //cretae an array with two dimensions
    /*initialized with 1 because there is only one method to reach any cell 
    in the first row or column(by moving to the right or down)*/

    for (int i = 1; i < row; i++) 
        for (int j = 1; j < column; j++) 
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
           //two ways : by moving to the right and down

    return dp[row - 1][column - 1];
}

int main() {
    int row, column;
    cout << "Enter the dimensions of the grid (m and n): ";
    cin >> row >> column;
    cout << "Total number of unique paths: " << countPaths(row, column) << endl;
    return 0;
}
