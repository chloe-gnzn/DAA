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
    int getBalance(node* gp){
        if(!gp) return 0;
        int lh = gp->left ? gp->left->height() : -1;
        int rh = gp->right ? gp->right->height() : -1;
        return lh-rh;
    }
    
    
    // TODO perform post-processing by checking for violation after insertion
    // from the node inserted (or from its parent) until the root
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
    				tree->addRight(n, num);
    				node* par = n;
                    while (par) {
                        int lh = par->left ? par->left->height() : -1;
                        int rh = par->right ? par->right->height() : -1;
                
                        if (abs(lh - rh) > 1) {
                            restructure(par);
                            break;
                        }
                
                        par = par->parent;
                    }
                    return n;
    				
    			} else {
    				return insert_node(n->right, num);
    			}
    		} else {
    			if (!n->left) {
    				tree->addLeft(n, num);
    				
    				node* par = n;
                    while (par) {
                        int lh = par->left ? par->left->height() : -1;
                        int rh = par->right ? par->right->height() : -1;
                
                        if (abs(lh - rh) > 1) {
                            restructure(par);
                            break;
                        }
                
                        par = par->parent;
                    }
                    return n;
    			} else {
    				return insert_node(n->left, num);
    			}
    		}
    }

    // TODO perform post-processing by checking for violation after deletion
    // from the parent of the node removed until the root
    bool remove(int num) {
        return remove_node(tree->getRoot(), num);
    }

    bool remove_node(node* n, int num) {
        if (n == NULL) return false;
    
        if (num > n->elem) {
            return remove_node(n->right, num);
        } 
        else if (num < n->elem) {
            return remove_node(n->left, num);
        } 
        else {
            node* par = n->parent; 
    
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                int rem = r->elem; 
                remove_node(r, rem);
    
                n->elem = rem;
                
                return true;
            } 
            else {
                tree->remove(n);
                
                node* curr = par;
                while (curr) {
                    int lh = curr->left ? curr->left->height() : -1;
                    int rh = curr->right ? curr->right->height() : -1;
    
                    if (abs(lh - rh) > 1) {
                        restructure(curr); 
                    }
                    curr = curr->parent;
                }
                return true;
            }
        }
        return false;
    }


    // TODO copy and paste your completed restructure method here
  bool restructure(node* gp) {
        
        node* par; // parent        //our y
        // TODO find parent
        //y
        int bal = getBalance(gp);
        if(bal > 0){
            par = gp->left;
        }else{
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
        }else{
            child = par->right;
        }
        
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
        }

        // z
        //   \
        //     y
        //    /
        //   x
        else if (gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            cout << "ZIGZAGLEFT" << endl;
            zigright(child);
            zigleft(child);
            
        }

        //      z
        //     /
        //    y
        //   /
        //  x
        else if (!gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            zigright(par);
            cout << "ZIGRIGHT" << endl;
        }

        //       z
        //     /
        //    y
        //     \
        //      x
        else {
            // TODO call to either zigleft or zigright or both
            zigleft(child);
            zigright(child);
            cout << "ZIGZAGRIGHT" << endl;
        }

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