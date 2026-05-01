#include "node.hpp"
#include <iostream>
#include <climits>
using namespace std;
class Heap {
	
	node** arr;
	int heapSize;
	int cap;
	
	int left(int i){ return i * 2 + 1; }
	int right(int i){ return i * 2 + 2; }
	int parent(int i){ return (i-1) / 2; }
	
	public:
	Heap(){
	    cap = 101;
	    arr = (node**)malloc(cap * sizeof(node*));
	    heapSize = 0;
	}
	
    // TODO insert
	void insert(node* n) {
        arr[heapSize] = n;
        
        int i = heapSize++;
        
        while(i > 0 && arr[i]->weight < arr[parent(i)]->weight){
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
	}

    // TODO removeMin
	node* removeMin() {
	    if(heapSize == 0) return nullptr;
	    
	    node* root = arr[0];
	    arr[0] = arr[--heapSize];
	   
	    int i = 0;
	    while(left(i) < heapSize){
	        int j = left(i);
	        
	        if(j+1 < heapSize && arr[j+1]->weight < arr[j]->weight){
	            j++;
	        }
	        
	        if(arr[i]->weight <= arr[j]->weight){
	            break;
	        }
	        
	        swap(arr[i], arr[j]);
	        i = j;
	    }
	    return root;
	}

    // TODO size
	int size() {
		return heapSize;
	}
};
