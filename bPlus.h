#ifndef BPLUS
#define BPLUS
#include <iostream>

using namespace std;

class bPlus{
	private:
		struct Node{
			int key;
			int key2;
			int key3;

			Node *left;
			Node *center;
			Node *right;
			Node *four;

			Node *next;
			Node *previous;
		};
		Node *root;

		int getMiddle(int, int, int);
		int getHigh(int, int, int);
		int getLow(int, int, int);
		void promoteRoot(int, int, int, Node *);
		void splitLeaf(int, int, int, Node *);
		void bigSplit(int, int, int, Node *);
		Node *makeNode(Node*, int);

		void rInsert(Node*, int);

		void displayNode(Node*);

		void splitRoot(Node *);
		void splitNonLeaf(int, int, int, Node *);
		void biggerSplit(int, int, int, Node *);
	public:
		bPlus();

		bool insert(int);
		int find(int);
		void display(); 
		void check();
		void checkRoots(Node *);


};

#endif