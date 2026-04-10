#include <iostream>
using namespace std;

struct node {
    node* parent;
    node* right;
    node* left;
    int elem;

    // TODO paste your height method here
    int height() {
        int lh = left ? left->height() : -1;
        int rh = right ? right->height() : -1;
        return 1 + max(lh, rh);
    }
};