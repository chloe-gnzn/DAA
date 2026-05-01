#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

int knapsnack(int* itemValue, int* itemWeight, int n, int W);

int main(){
    int n, W;
    
    cout << "Enter number of items and weight capacity: ";
    cin >> n >> W;
    
    int* itemValue = (int*)malloc(n * sizeof(int));
    int* itemWeight = (int*)malloc(W * sizeof(int));
    
    cout << "Enter value and weight of each item: "<< endl;
    for(int i = 0; i < n; i++){
        cin >> itemValue[i] >> itemWeight[i];
    }
    
    cout << "Maximum value in Knapsack = " << knapsnack(itemValue, itemWeight, n, W);
    
}

int knapsnack(int* itemValue, int* itemWeight, int n, int W){
    int* max = (int*)calloc((W+1), sizeof(int));
    
    for(int i = 0; i < n; i++){
        for(int j = W; j>= itemWeight[i]; j--){
            max[j] = std::max(max[j], itemValue[i] + max[j - itemWeight[i]]);
        }
        
    }
    int res = max[W];
    delete[] max;
    return res;
}
