#include "bplus.h"

bPlus::bPlus(){ root = NULL; }

bool bPlus::insert(int in){
	int middle, low, high;
	Node *pointer;

	if(!root){
		root = makeNode(pointer, in); //returns a new node pointer 
		return true;
	}
	else if(root){
		pointer = root;
    
		if(!pointer->key2 && !pointer->left){
			pointer->key2 = in;		//bc what if the tree is full and you randomly insert the wrong#
			return true;
		}
		else if(pointer->left){
			rInsert(pointer, in);	
		}

		if(pointer->key && pointer->key2 && !pointer->left){ 
			middle = getMiddle(in, pointer->key, pointer->key2);
			high = getHigh(in, pointer->key, pointer->key2);
			low = getLow(in, pointer->key, pointer->key2);
			promoteRoot(middle, high, low, pointer);
			return true;
		}
	}

	return true;
}

int bPlus::find(int rtr){
	Node *pointer = root;

	while(pointer->left){
		if(rtr < pointer->key){
			pointer = pointer->left;
		}
		else if(rtr >= pointer->key){
			if(pointer->key2 == 0){
				pointer = pointer->right;
			}
			else if(pointer->key2 != 0){
				if(rtr < pointer->key2){
					pointer = pointer->center;
				}
				else if(rtr >= pointer->key2){
					pointer = pointer->right;
				}
			}
		}
	} //end while

	if(rtr == pointer->key){
		return pointer->key;
	}
	else if(rtr != pointer->key){
		if(rtr == pointer->key2)
			return pointer->key2;
		else return -1;
	}
	return -1;
}

void bPlus::rInsert(Node *pointer, int in){
	int middle, high, low;

	if(in < pointer->key && pointer->left){ 
		pointer = pointer->left;
		rInsert(pointer, in);
		// else if(!pointer->left){ //thus must be in a leaf
		// 	//insertLeaf(pointer, in);
		// }
	}
	else if(in >= pointer->key && pointer->key2 == 0 && pointer->left == NULL){
		pointer->key2 = in;
		return;
	}
	else if(in >= pointer->key && pointer->key2 == 0 && pointer->left != NULL){
		pointer = pointer->right;
		rInsert(pointer, in);
	}
	else if(in >= pointer->key && in < pointer->key2){
		//placeholder
	}
	else if(in >= pointer->key2 && !pointer->left && !pointer->previous->center){
		middle = getMiddle(in, pointer->key, pointer->key2);
		high = getHigh(in, pointer->key, pointer->key2);
		low = getLow(in, pointer->key, pointer->key2);
		splitLeaf(middle, high, low, pointer);
		return;
	}
	else if(in >= pointer->key2 && pointer->left){
		pointer = pointer->right;
		rInsert(pointer, in);
	}
	else if(in >= pointer->key2 && !pointer->left && pointer->previous->center){
		pointer->key2 = getMiddle(in, pointer->key, pointer->key2);
		pointer->key3 = getHigh(in, pointer->key, pointer->key2);
		pointer->key = getLow(in, pointer->key, pointer->key2);
		bigSplit(pointer->key2, pointer->key3, pointer->key, pointer);
		return;
	}
}

void bPlus::display(){
	Node *pointer = root;

	while(pointer->left){
		pointer = pointer->left;
	}
	while(pointer != NULL){
		displayNode(pointer);
		pointer = pointer->next;
	}
}

int bPlus::getMiddle(int a, int b, int c){
	if(a == b == c)
		return a;
	if((c >= a && a >= b) || (b >= a && a >= c))
		return a;
	if((a >= b && b >= c) || (c >= b && b >= a))
		return b;
	if((a >= c && c >= b) || (b >= c && c >= a))
		return c;

	return -1;
}

int bPlus::getHigh(int a, int b, int c){
	int high = a;

	if(b >= high) high = b;

	if(c >= high) high = c;

	return high;
}

int bPlus::getLow(int a, int b, int c){
	int low = a;

	if(b <= low) low = b;

	if(c <= low) low = c;

	return low;
}

void bPlus::promoteRoot(int mid, int hi, int lo, Node *pointer){
	Node *left = makeNode(pointer->left, lo);	
	Node *right = makeNode(pointer->right, mid);

	pointer->left = left;
	pointer->right = right;

	pointer->key2 = 0;
	pointer->key = mid;

	right->key2 = hi;
	left->next = right;
	
	right->previous = pointer;
	left->previous = pointer;
}

void bPlus::splitLeaf(int mid, int hi, int lo, Node *pointer){
	Node *cent = makeNode(pointer->previous->center, lo);

	pointer->previous->center = cent;
	pointer->previous->left->next = cent; //aka center
	cent->next = pointer;

	pointer->key = mid;
	pointer->key2 = hi;
	
	cent->previous = pointer->previous;
	pointer->previous->key2 = mid;
	pointer->previous->right = pointer;
}

void bPlus::splitNonLeaf(int mid, int hi, int lo, Node *pointer){
	Node *cent = makeNode(pointer->previous->center, lo);
	pointer->previous->center = cent;

	cent->left = pointer->left;
	cent->left->previous = cent;
	cent->right = pointer->center;


	cent->previous = pointer->previous;

	pointer->left = pointer->right;
	pointer->right = pointer->four;
	pointer->center = NULL;
	pointer->key = hi;
	pointer->key2 = pointer->key3 = 0;

	pointer->previous->key2 = mid;


	//new stuff


	//cout << "love " << endl;
	//fault here

	cent->right->previous = cent;

	//fault here
	//cout << "fault" << endl;


	pointer->four = NULL;

}	

void bPlus::biggerSplit(int mid, int hi, int lo, Node *pointer){
	while(pointer->previous->key2 != 0){
		Node *temp = makeNode(pointer->previous->four, pointer->key3);

		pointer->previous->four = temp;
		temp->previous = pointer->previous;

		pointer->previous->key3 = pointer->key2;
		pointer->key2 = pointer->key3 = 0;

		temp->right = pointer->four;
		temp->right->previous = temp;
		pointer->four = NULL;

		temp->left = pointer->right;
		temp->left->previous = temp;
		pointer->right = NULL;

		pointer->right = pointer->center;
		pointer->center = NULL;

		//checkRoots(temp);

		pointer = pointer->previous;

		if(pointer == root){
			//check();
			splitRoot(pointer);
			return;
		}
	}
	splitNonLeaf(pointer->key2, pointer->key3, pointer->key, pointer);
}

void bPlus::bigSplit(int mid, int hi, int lo, Node *pointer){
	while(pointer->key3){
		if(pointer == root && pointer->key2 != 0){
			splitRoot(pointer);
			return;
		}
		else if(pointer == root && pointer->key2 == 0){
			return;
		}

		//THIS!! (:
		if(pointer->previous->key2 == 0){
			splitNonLeaf(pointer->key2, pointer->key3, pointer->key, pointer);
			return;
		}

		if(pointer->previous == root && pointer->left){
			biggerSplit(pointer->key2, pointer->key3, pointer->key, pointer);
			return;
		}

		if(pointer->previous->key2 != 0 && pointer->left){
			biggerSplit(pointer->key2, pointer->key3, pointer->key, pointer);
			return;
		}

		Node *temp = makeNode(pointer->previous->four, mid);
		temp->key2 = hi;
		pointer->previous->four = temp;
		pointer->previous->key3 = mid;

		pointer->previous->right->next = temp;
		pointer->previous->right->key2 = pointer->previous->right->key3 = 0;

		temp->previous = pointer->previous;
		pointer = pointer->previous;
	}
}

void bPlus::splitRoot(Node *pointer){
	Node *newRoot = new Node;
	Node *newRight = new Node;

	newRoot->key = pointer->key2;
	newRoot->key2 = newRoot->key3 = 0;
	newRoot->left = pointer;
	newRoot->right = newRight;
	newRoot->center = newRoot->next = NULL;
	root = newRoot;

	newRight->key = pointer->key3;
	newRight->key2 = newRight->key3 = 0;
	newRight->left = pointer->right;
	newRight->right = pointer->four;
	newRight->center = newRight->next = NULL;
	newRight->previous = newRoot;
	newRight->right->previous = newRight->left->previous = newRight;

	//pointer->key = unchanged;
	pointer->key2 = pointer->key3 = 0;
	pointer->right = pointer->center;
	//pointer->left = unchanged
	pointer->center = pointer->next = pointer->four = NULL;
	pointer->previous = newRoot;
	pointer->left->previous = pointer->right->previous = pointer;

	return;
}

bPlus::Node *bPlus::makeNode(Node *making, int k){
	making = new Node;
	making->left = making->right = making->center = making->next = NULL;
	making->key = k;
	making->key2 = 0;
	return making;
}

void bPlus::displayNode(Node* display){
	cout << "key 1 = " << display->key << endl;
	if(display->key2)
		cout << "key 2 = " << display->key2 << endl;
	else
		cout << "key 2 = 0" << endl;
	if(display->key3)
		cout << "key 3 = " << display->key3 << endl;

}

void bPlus::check(){
	Node *pointer = root;
	cout << "CHECKING" << endl;

	displayNode(pointer);

	displayNode(pointer->left);

	if(pointer->center){
		cout << "center" << endl;
		displayNode(pointer->center);
	}

	displayNode(pointer->right);

	if(pointer->four) {
		cout << "four " << endl;
		displayNode(pointer->four);
	}

}

void bPlus::checkRoots(Node *pointer){
	cout << "checking roots" << endl;

	displayNode(pointer);

	if(pointer->left){
		cout << "left" << endl;
		displayNode(pointer->left);
	} 
	if(pointer->right){
		cout << "right " << endl;
		displayNode(pointer->right);
	}
	if(pointer->center){
		cout << "center " << endl;
		displayNode(pointer->center);
	}
}











