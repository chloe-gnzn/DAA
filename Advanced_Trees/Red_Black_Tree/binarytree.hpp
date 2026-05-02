#include <iostream>
#include "node.hpp"
using namespace std;

class BinaryTree{
    node* root;
    int size;

    node* create_node(int e, node* parent){
        node* n = new node();
        n->elem = e;
        n->parent = parent;

        return n;
    }

    public: 
    node* addRoot(int e){
        if(root){
            cout << "Already has root"; 
            return nullptr;
        } 

        node* n = create_node(e, nullptr);
        root = n;
        n->isRed = false;
        size++;
        return n;
    }

    node* getRoot(){
        return root;
    }

    node* addRight(node* p, int e){
        if(p->right){
            cout << "Already has a right child: " << p->right->elem; 
            return NULL;
        } 

        node* n = create_node(e, p);
        p->right = n;
        size++;
        return n;
    }

    node* addLeft(node* p, int e){
        if(p->left){
            cout << "Already has a left child: " << p->left->elem; 
            return NULL;
        } 

        node* n = create_node(e, p);
        p->left = n;
        size++;
        return n;
    }

    void zigleft(node* curr){
        node* par = curr->parent;
        if(!par) return;
        node* gp = par->parent;

        if(root == par){
            root = curr;
        }else if(gp->left == par){
            gp->left = curr;
        }else{
            gp->right = curr;
        }

        curr->parent = gp;
        par->right = curr->left;
        if(curr->left) curr->left->parent = par;
        curr->left = par;
        par->parent = curr;
        
    }

    void zigright(node* curr) {
        node* par = curr->parent;
        if(!par) return;
        node* grandP = par->parent;
        
        if(root == par){
            root = curr;
        }else if(grandP && grandP->left == par){
            grandP->left = curr;
        }else{
            grandP->right = curr;
        }
        
        curr->parent = grandP;
        par->left = curr->right;
        if(curr->right) curr->right->parent = par;
        curr->right = par;
        par->parent = curr;
  
    }

    bool search(int num){
        return search_node(getRoot(), num);
    }

    bool search_node(node* n, int num){
        if(!n) return false;

        if(n->elem == num){
            return true;
        }

        if(num < n->elem){
            return search_node(n->left, num);
        }else if(num > n->elem){
            return search_node(n->right, num);
        }
        return false;
    }

    node* insert(int num){
        node* n = getRoot();
        if(!n) return addRoot(num);

        node* inserted = insert_node(n, num);
        if(!inserted) return nullptr;

        if(inserted->parent && inserted->parent->isRed){
            handleDoubleRed(inserted);
        }
        return inserted;
    }

    node* insert_node(node* n, int num){
        if(!n) return nullptr;
        
        if(n->elem == num)return nullptr;
        
        if(num < n->elem){
            if(!n->left){
                return addLeft(n, num);
            }else{
                return insert_node(n->left, num);
            }
        }else{
            if(!n->right){
                return addRight(n, num);
            }else{
                return insert_node(n->right, num);
            }
        }
    }

    bool restructure(node* curr){
        node* par = curr->parent;
        node* gp = par->parent;

        if(!par || !gp) return false;

        bool gtop_right = (gp->right == par);

        bool ptoc_right = (par->right == curr);

        if(gtop_right && ptoc_right){
            zigleft(par);
            par->isRed = false;
            gp->isRed = true;
            curr->isRed = true;
            cout << "ZIGLEFT" << endl;
        }else if(gtop_right && !ptoc_right){
            zigright(curr);
            zigleft(curr);
            curr->isRed = false;
            gp->isRed = true;
            par->isRed = true;
            cout<< "ZIGZAGLEFT" << endl;
        }else if(!gtop_right && !ptoc_right){
            zigright(par);
            gp->isRed = true;
            par->isRed = false;
            curr->isRed = true;
            cout << "ZIGRIGHT"<<endl;
        }else if(!gtop_right && ptoc_right){
            zigleft(curr);
            zigright(curr);

            curr->isRed = false;
            par->isRed = true;
            gp->isRed = true;
            cout<< "ZIGZAGRIGHT" << endl;
        }

        return true;
    }

    void handleDoubleRed(node* curr){
        if(curr == root){
            curr->isRed = false;
            return;
        }

        node* par = curr->parent;
        if(!par->isRed) return;

        node* gp = par->parent;
        if(!gp) return;

        node* unc;

        if(gp->left == par){
            unc = gp->right;
        }else{
            unc = gp->left;
        }

        if(unc != nullptr && unc->isRed){
            unc->isRed = false;
            par->isRed = false;
            gp->isRed = true;

            handleDoubleRed(gp);

        }else{
            restructure(curr);
            
        }

        if(gp == root){
            gp->isRed = false;
        }
    }

    void print() {
		cout << "Size: " << size << endl;
		if (!root) {
			cout << "EMPTY" << endl;
			return;
		}
		node* curr = root;
		print_node("", root, false);
        cout << "Status: " << check_parent(root, NULL) << endl;
	}


    void print_node(string prefix, node* n, bool isLeft) {
		cout << prefix;
        cout << (isLeft ? "+--L: " : "+--R: " );
        cout << n->elem << ": " << (n->isRed ? "RED" : "BLACK") << endl;
		if (n->left) {
			print_node(prefix + "|   ", n->left, true);
		}
		if (n->right) {
			print_node(prefix + "|   ", n->right, false);
		}
    }

    bool check_parent(node* curr, node* par) {
        if (!curr) {
            return true;
        }
        if (curr->parent != par) {
            if (!curr->parent) {
                cout << "Illegal parent of " << curr->elem << ": NULL -- must be " << par->elem << endl;
            } else if (!par) {
                cout << "Illegal parent of " << curr->elem << ": " << curr->parent->elem << "must be NULL" << endl;
            } else {
                cout << "Illegal parent of " << curr->elem << ": " << curr->parent->elem << " -- must be " << par->elem << endl;
            }
            return false;
        }
        return check_parent(curr->left, curr) && check_parent(curr->right, curr);
    }

};