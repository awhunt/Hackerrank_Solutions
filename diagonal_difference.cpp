#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the diagonalDifference function below.
 */
int diagonalDifference(vector<vector<int>> a) {
    /*
     * Write your code here.
     */
    
    int diag1 = 0;
    int diag2 = 0;
    
    //************************
    // NAIVE SOLUTION O(n^2)
    //************************
//     for (size_t i = 0; i < a.size(); i++) {
//         for (size_t j = 0; j < a[i].size(); j++){
//             if (i == j) 
//                 diag1 += a[i][j]; 
//             if ((i + j) == (a.size() - 1)) 
//                 diag2 += a[i][j];
//         }
//     }
    
    //************************
    // BETTER SOLUTION O(n)
    //************************
    for(size_t i = 0; i < a.size(); i++) {
        diag1 += a[i][i];
        diag2 += a[i][((a.size() - 1) - i)];
    }
    
    return abs(diag1 - diag2);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> a(n);
    for (int a_row_itr = 0; a_row_itr < n; a_row_itr++) {
        a[a_row_itr].resize(n);

        for (int a_column_itr = 0; a_column_itr < n; a_column_itr++) {
            cin >> a[a_row_itr][a_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = diagonalDifference(a);

    fout << result << "\n";

    fout.close();

    return 0;
}