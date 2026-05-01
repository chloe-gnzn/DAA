#include "heap.hpp"

// TODO huffman
node* huffman_code(Heap* heap) {
    if(heap->size() == 0) return nullptr;
    
    while(heap->size() > 1){
        node* left = heap->removeMin();
        node* right = heap->removeMin();
        
        node* par = new node('$', left->weight + right->weight);
        par->left = left;
        par->right = right;
        
        left->parent = par;
        right->parent = par;
        
        heap->insert(par);
    }
    
    node* res = heap->removeMin();
    return res;
}
