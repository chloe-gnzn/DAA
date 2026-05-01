#include <iostream>
#include <cstring>
#include "huffman.hpp"
using namespace std;

int main(int argc, char** argv) {
	int w;
	char c;
	node* leaves[25];
	int size = 0;
	Heap* heap = new Heap();

	cout << "Enter 0 for weight to stop." << endl;
	while (true) {
		cout << "Enter char and weight: ";
		cin >> c >> w;
		if (w == 0) {
			break;
		}
		node* n = new node(c,w);
		leaves[size++] = n;
		heap->insert(n);
	}

	node* root = huffman_code(heap);
	int filesize = 0;
	for (int i = 0; i < size; i++) {
		int mysize = leaves[i]->getCode().length() * leaves[i]->weight;
		cout << leaves[i]->ch << "(" << leaves[i]->weight << ") - " << leaves[i]->getCode() << " = "<< mysize <<" bits"<< endl;
		filesize += mysize;
	}
	cout << "File Size = " << filesize << " bits" << endl;
	return 0;
}
