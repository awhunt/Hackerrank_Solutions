#include <iostream>
#include <deque> 
#include <limits>
using namespace std;

// This is all my own code, 
// this was before hackerrank provided parsing functions 

void printKMax(int arr[], int n, int k){
   deque<int> deck;
   // fill the deque to capacity
   for (int i = 0; i < k; i++) {
       deck.push_back(arr[i]);
   }
    int max = - std::numeric_limits<double>::infinity();
    int max_index = 0;
    for (int j = 0; j < k; j++) {
        if (deck[j] > max) {
            max = deck[j];
            max_index = j;
        }
    }
    cout << deck[max_index] << " ";
    //check each subarray
    for (int i = k; i < n; i++) {
        deck.pop_front();
        deck.push_back(arr[i]);
        max_index--;
        
        //end of subarray, update max_index
        if (max_index == -1) {
            int max = - std::numeric_limits<double>::infinity();
            for (int j = 0; j < k; j++) {
                if (deck[j] > max) {
                    max = deck[j];
                    max_index = j;
                }
            }
        }
        
        //compare next in line
        else if (deck[max_index] < arr[i]) {
            max_index = deck.size() - 1;
        }   
        cout << deck[max_index] << " ";
    }
    cout << endl;
}
int main(){
  
   int t;
   cin >> t;
   while(t>0) {
      int n,k;
       cin >> n >> k;
       int i;
       int arr[n];
       for(i=0;i<n;i++)
            cin >> arr[i];
       printKMax(arr, n, k);
       t--;
     }
     return 0;
}