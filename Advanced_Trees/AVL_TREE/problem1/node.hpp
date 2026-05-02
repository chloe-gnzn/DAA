#include <iostream>
using namespace std;
struct node {
    node* parent;
    node* right;
    node* left;
    int elem;
    
    int getHeight(){
        int lh = left ? left->getHeight() : -1;
        int rh = right ? right->getHeight() : -1;
        return 1 + max(lh, rh);
    }
};