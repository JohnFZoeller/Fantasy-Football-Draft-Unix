// ------------------------------------------------ binTree.h ------------------------------------------------------- -
// John Zoeller, CSS 343 A
// Creation Date: 1/16/16
// Date of Last Modification: 1/30/16
// -------------------------------------------------------------------------------------------------------------------- 
// Purpose - Outlines a Binary Search Tree class
// -------------------------------------------------------------------------------------------------------------------- 
// Notes on specifications, special algorithms, and assumptions:
//
// --------------------------------------------------------------------------------------------------------------------
#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <string>
#include <fstream>
#include "nodedata.h"

using namespace std;

class BinTree
{
    friend ostream & operator<<(ostream &, const BinTree &);

    private:
        struct Node
        {
            NodeData* data;
            Node* left;
            Node* right;
        };
        Node* root;

    //PRIVATE HELPERS
    void inorderHelper(NodeData*arr[], int &index, Node *node) const;
    void sideways(Node*, int) const;        
    void makeEmpty(Node*);
    Node *balancedBuild(NodeData *arr[], int, int) const;
    Node *deepCop(const Node *sub) const;
    Node *retr(const NodeData &key, Node *sub) const;
    bool compare(const Node *john, const Node *zoeller) const;
    int getH(Node *sub) const;
    int leafHelper(Node*) const;
    string displayHelp(string, Node *node) const;

    //NEW INSERT


    public:

        //CONSTRUCTORS / DESTRUCTOR
        BinTree();							
        BinTree(const BinTree &);				      
        ~BinTree();                                                                                           
        		
        //UTILITIES
        bool isEmpty() const;
        void makeEmpty();

        //OVERLOADS
        BinTree& operator=(const BinTree &);
        bool operator==(const BinTree &) const;
        bool operator!=(const BinTree &) const;

        //INSERT
        bool insert(NodeData*);

        //HEIGHT
        int getHeight (const NodeData &) const;

        //leaf - just for fun
        int getLeafCount() const;

        //RETREIVE
        bool retrieve(const NodeData &key, NodeData* &p) const;     

        //TREE / ARRAY
        void bstreeToArray(NodeData* []);
        void arrayToBSTree(NodeData* []);

        //DISPLAY SIDEWAYS
        void displaySideways() const;
};

#endif

