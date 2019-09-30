//Brian Solis
//Arren De Manuel
#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

template<typename Data>
class BST {

   protected:

      /** Pointer to the root of this BST, or 0 if the BST is empty */
      BSTNode<Data>* root;

      /** Number of Data items stored in this BST. */
      unsigned int isize;

      /** Height of this BST. */
      unsigned int iheight;

   public:

      /** define iterator as an aliased typename for BSTIterator<Data>. */
      typedef BSTIterator<Data> iterator;

      /** Default constructor.
        * Initialize an empty BST.
        */
      BST() : root(0), isize(0), iheight(0) {  }


      /** Default destructor.
        * Delete every node in this BST.
        */
      virtual ~BST() {
         deleteAll(root);
      }

      /** Given a reference to a Data item, insert a copy of it in this BST.
       *  Return  true if the item was added to this BST
       *  as a result of this call to insert,
       *  false if an item equal to this one was already in this BST.
       *  Note: This function should use only the '<' operator when comparing
       *  Data items. (should not use ==, >, <=, >=)  For the reasoning
       *  behind this, see the assignment writeup.
       */
      virtual bool insert(const Data& item) {
       	BSTNode<Data>* newnode = new BSTNode<Data>(item);
       	BSTNode<Data>* current = nullptr;
       	unsigned int current_height = 0;
	//If BST is empty, then make this node the new root
       	if( !root ){ 
        	root = newnode;
	 	isize++;

         	return true;
    	}
	//Else traverse the list
	else{
          	current = root;
		while( current->left || current->right ){
			//If new node is less than current node, place in the left subtree
			if( newnode->data < current->data){
				if( current->left ) {
					current = current->left;
					current_height++;
					continue;
				}
				else {
					newnode->parent = current;
					current->left = newnode;
					current_height++;
	 				isize++;
					if( iheight < current_height ) iheight = current_height;
					return true;
				}	 			
                        } 
			//If new node is greater than current node, place in right subtree
			else if( current->data < newnode->data ){
				if( current->right ) {
					current = current->right;
					current_height++;
					continue;
				}
				else {
					newnode->parent = current;
					current->right = newnode;
					current_height++;
	 				isize++;
					if( iheight < current_height ) iheight = current_height;
					return true;
				}
			} 
			//If node already exists, delete the new node
			else {
				delete newnode;
				return false;
			}
		}
		
		//If there is not children, place left if less than
		if( newnode->data < current->data){
			newnode->parent = current;
			current->left = newnode;
			current_height++;
 			isize++;
			if( iheight < current_height ) iheight = current_height;
				return true;
					 			
             	} 
		//Place right if greater than
		else if( current->data < newnode->data ){
			newnode->parent = current;
			current->right = newnode;
			current_height++;
 			isize++;
			if( iheight < current_height ) iheight = current_height;
				return true;
		} 
		//Delete if already existing
		else {
			delete newnode;
			return false;
		}
	}
      

	}	

      /** Find a Data item in the BST.
       *  Return an iterator pointing to the item, or pointing past
       *  the last node in the BST if not found.
       *  Note: This function should use only the '<' operator when comparing
       *  Data items. (should not use ==, >, <=, >=).  For the reasoning
       *  behind this, see the assignment writeup.
       */
      virtual iterator find(const Data& item) const {
        	BSTNode<Data>* current = root;
		
		while( current ) {
			if( item < current->data){
				current = current->left;
			}
			else if(current->data < item){
				current = current->right;
			}
			else{
				break;
			}  
    		}
		return BST::iterator(current);
	}
      /** Return the number of items currently in the BST.
       *  
       */
      unsigned int size() const {
         return isize;
      }

      /** Return the height of the BST.
       * The height of an empty tree is -1 and the height of a tree
       * with only one node is 0.
       *  
       */
      unsigned int height() const {
        
         return iheight;
      }


      /** Return true if the BST is empty, else false.
       */
      bool empty() const {
         return isize == 0;
      }

      /** Return an iterator pointing to the first item in the BST (not the root).
       */
      iterator begin() const {
         return BST::iterator(first(root));
      }

      /** Return an iterator pointing past the last item in the BST.
       */
      iterator end() const {
         return typename BST<Data>::iterator(0);
      }


      /** Inorder traverse BST, print out the data of each node in ascending order.
       * Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
       * Pseudo Code:
       * if current node is null: return;
       * recursively traverse left sub-tree
       * print current node data
       * recursively traverse right sub-tree
       * 
       */
      void inoder( BSTNode<Data>* n ){  
	if (!n) {
		return;
	}	
	
       	else {
		inorder( n->left);
		cout << n->data;
		inorder( n->right);
	 }
	}
	//Calls the recursive function
     void inorder() const { inorder(root); }


   private:

      /** Find the first element of the BST
       *  Go to the leftmost node  
       */ 
      static BSTNode<Data>* first(BSTNode<Data>* n) {
        if (!n) return nullptr;
	while(n->left != nullptr){
		n = n->left;
	}
	return n;
      }

      /** do a postorder traversal, deleting nodes
       *   
       */
      static void deleteAll(BSTNode<Data>* n) {
         /* Pseudo Code:
            if current node is null: return;
            recursively delete left sub-tree
            recursively delete right sub-tree
            delete current node
            */
	BSTNode<Data>* right = nullptr;
	if( !n ){
		return;
	}
        else {	
		deleteAll(n->left);
		right = n->right;
		delete n;
		deleteAll(right);
	}
      }
};


#endif //BST_HPP
