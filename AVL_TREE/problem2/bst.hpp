#include "mybinarytree.hpp"

class BST {
	BinaryTree* tree = new MyBinaryTree();

	public:
	bool search(int num) {
		return search_node(tree->getRoot(), num);
	}

	bool search_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
			return true;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num);
		} else {
			return search_node(n->left, num);
		}
	}

	node* insert(int num) {
		node* n = tree->getRoot();
		if (n == NULL) {
			return tree->addRoot(num);
		}
		return insert_node(n, num);
	}

	node* insert_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
			return NULL;
		}
		if (num > n->elem) {
			if (!n->right) {
				return tree->addRight(n, num);
			} else {
				return insert_node(n->right, num);
			}
		} else {
			if (!n->left) {
				return tree->addLeft(n, num);
			} else {
				return insert_node(n->left, num);
			}
		}
	}

    bool remove(int num) {
        return remove_node(tree->getRoot(), num);
    }

	bool remove_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                int rem = tree->remove(r);
                n->elem = rem;
            } else {
    			tree->remove(n);
            }
            return true;
		}
		if (num > n->elem) {
			return remove_node(n->right, num);
		} else {
			return remove_node(n->left, num);
		}
	}
    
    int getBalance(node* gp){
        if(!gp) return -1;
        int lh = gp->left ? gp->left->height() : -1;
        int rh = gp->right ? gp->right->height() : -1;
        return lh-rh;
    }
    // GIVEN the grandparent (or z), find the parent (or y), and the child (or x).
    bool restructure(node* gp) {
        
        node* par; // parent        //our y
        // TODO find parent
        //y
        int bal = getBalance(gp);
        if(bal >= 1){
            par = gp->left;
        }else if(bal <=0){
            par = gp->right;
        }
        
        
        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        node* child;
        // TODO find child
        //x
        
         bal = getBalance(par);
        if(bal == 0){
            if(gtop_right){
                child = par->right;
            }else{
                child = par->left;
            }
        }else if(bal > 0){
            child = par->left;
        }else if(bal < 0){
            child = par->right;
        }
        
        /*child = par->left;
        if(par->right && par->right->height() > (child ? child->height() : -1)){
            child = par->right;
        }*/
        
        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

        // z
        //  \
        //   y
        //    \
        //     x
        if (gtop_right && ptoc_right) {
            // TODO call to either zigleft or zigright or both
            zigleft(par);
            cout << "ZIGLEFT" << endl;
            /*zigright(par);
            zigleft(gp);*/
        }

        // z
        //   \
        //     y
        //    /
        //   x
        else if (gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            //zigleft(gp);
            cout << "ZIGZAGLEFT" << endl;
            /*zigright(child);
            zigleft(par);*/
            zigright(child);
            zigleft(child);
            
        }

        //     z
        //    /
        //   y
        //  /
        // x
        else if (!gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            zigright(par);
            cout << "ZIGRIGHT" << endl;
        }

        //      z
        //    /
        //  y
        //   \
        //    x
        else {
            // TODO call to either zigleft or zigright or both
            /*zigleft(child);
            zigright(par);*/
            zigleft(child);
            zigright(child);
            //zigright(par);
            cout << "ZIGZAGRIGHT" << endl;
        }
        
        /*if(par == gp->right){
            if(child == par->left){
                zigright(par);
                zigleft(gp);
            }else{
                zigleft(gp);
            }
        }else{
            if(child == par->left){
                zigright(gp);
            }else{
                zigleft(par);
                zigright(gp);
            }
        }*/

        return true;
    }

    void zigleft(node* curr) {
        tree->zigleft(curr);
    }

    void zigright(node* curr) {
        tree->zigright(curr);
    }

	void print() {
		tree->print();
	}
};