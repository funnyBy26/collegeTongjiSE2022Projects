/*----------------------------------------------
name : ¸¶±¦Ó¨
ID : 2251654
phone number:19145163653
e-mail:987596476@qq.com
last edit time: 2024.4.7
-----------------------------------------------*/
#include <iostream>
#include<algorithm>
#include <vector>
using namespace std;

/**********************************************************
* function name: input_array
* type of ret: bool
* function: used to input the array of scores nameing scores
**********************************************************/
bool inputArray(vector<int>& scores) {
    int temp_num = -1;//a temporary variable to represent score
    cout << "Please enter a score array(separated ny spaces,an enter entered to the end): " << endl;
    while (true) {
        cin >> temp_num;
        if (temp_num < 0 || cin.fail()) {
            cout << "wrong input!!! fail!!!" << endl;
            exit(-1);
        }
        else {
            scores.push_back(temp_num);
            if (cin.peek() == '\n')//when read an enter,finish the procedure of entering.
                break;
        }
    }
    return true;
}

/**********************************************************
* function name: canPlayer1Win
* type of ret: bool
* function: used to judge if can player1 always win
**********************************************************/
bool canPlayer1Win(const vector<int>& scores,int sum_1,int sum_2,int left,int right,bool turnOfPlayer1) {
    if (left > right)//the case indicate that no number in the array can be used.
        return sum_1 > sum_2;//so it is time to compare the totsl score of between player1 and 2

    if (turnOfPlayer1)//player1's turn,select at least one case between left and right to win over player2
        return canPlayer1Win(scores, sum_1 + scores[left], sum_2, left + 1, right, false) || canPlayer1Win(scores, sum_1 + scores[right], sum_2, left, right - 1, false);
    else//player2's turn,,select a must-win circumstance that no matter choose left or right player! will win!
        return canPlayer1Win(scores, sum_1, sum_2 + scores[left], left + 1, right, true) && canPlayer1Win(scores, sum_1, sum_2 + scores[right], left, right - 1, true);
}

int main() {
    vector<int>scores;//the array for scores
    inputArray(scores);//enter the array of scores
    
    bool player1Win = canPlayer1Win(scores, 0, 0, 0, scores.size() - 1, 1);//to judge if player1 can win

    cout << "Can the first player1 win?" << endl;

    if (player1Win)
        cout << "true" << endl;
    else
        cout << "false" << endl;


    return 0;
}
