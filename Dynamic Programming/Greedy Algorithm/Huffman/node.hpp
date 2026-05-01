#include <iostream>
#include <string>
using namespace std;

struct node {
	char ch;
	int weight;
	node *left, *right, *parent;

	node(char c, int w) : ch(c), weight(w), left(nullptr), right(nullptr), parent(nullptr) {};

	// TODO getCode
	string getCode() {
	    if(!parent && !right && !left){
	        return "0";
	    }
	    
	    node* curr = this;
	    string code = "";
	    while(curr->parent != nullptr){
	        node* par = curr->parent;
	        if(par->left == curr){
	            code = "0" + code;
	        }else if(par->right == curr){
	            code = "1" + code;
	        }
	        curr = par;
	    }
	    
	    return code;
	}
};
