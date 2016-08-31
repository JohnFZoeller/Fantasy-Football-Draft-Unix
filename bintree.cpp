// ------------------------------------------------ binTree.cpp --------------------------------------------------
// John Zoeller, CSS 343 A
// Creation Date: 1/16/16
// Date of Last Modification: 1/30/16
// -------------------------------------------------------------------------------------------------------------------- 
// Purpose - Implementation file for binTree.h
// -------------------------------------------------------------------------------------------------------------------- 
// Notes on specifications, special algorithms, and assumptions
//      1 - Assume that a user uses a tree with something in it when using the ostream operator
// --------------------------------------------------------------------------------------------------------------------
#include "bintree.h"
#include <iostream>

// ------------------------------------Overloaded Ostream----------------------------------------------- 
// Description: calls display help, returns ostream out
// -------------------------------------------------------------------------------------------------------------
ostream & operator<<(ostream &out, const BinTree & rhs)
{
    if(rhs.root != NULL)
        out << rhs.displayHelp("", rhs.root) << endl;

    return out;
}

// ------------------------------------Display Help----------------------------------------------- 
// Description: Displays contents of tree recursively inorder
// -------------------------------------------------------------------------------------------------------------
string BinTree::displayHelp(string john, Node *node) const
{
    if(node->left != NULL)
        displayHelp(john, node->left);

    cout << *node->data << endl;

    if(node->right != NULL)
        displayHelp(john, node->right);

     return john;
}

// ------------------------------------Default Constructor----------------------------------------------- 
// Description: Sets root of tree to NULL
// -------------------------------------------------------------------------------------------------------------
BinTree::BinTree()
{
    root = NULL;
}

// ------------------------------------Copy Constructor----------------------------------------------- 
// Description: calls deepCop to make a deep copy of tree
// -------------------------------------------------------------------------------------------------------------
BinTree::BinTree(const BinTree &right)
{
    root = deepCop(right.root);
}

// ------------------------------------Assignment Operator----------------------------------------------- 
// Description: Avoids self assignment, assigns a deep copy of object to rhs
// -------------------------------------------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree &rhs)
{
    if(this != &rhs)
    {
        this->makeEmpty();
        root = deepCop(rhs.root);
    }
    return *this;
}

// ------------------------------------deepCop----------------------------------------------- 
// Description: recursively fills a new tree with the contents of sub
// -------------------------------------------------------------------------------------------------------------
BinTree::Node* BinTree::deepCop(const Node *sub) const
{
    if(sub == NULL)
        return NULL;

    Node *node = new Node;
    node->data = sub->data;

    node->left = deepCop(sub->left);
    node->right = deepCop(sub->right);

    return node;
}

// ------------------------------------Destructor----------------------------------------------- 
// Description: call makeEmpty
// -------------------------------------------------------------------------------------------------------------
BinTree::~BinTree()
{
    makeEmpty();
}

// ------------------------------------MakeEmpty----------------------------------------------- 
// Description: calls recursive makeEmpty
// -------------------------------------------------------------------------------------------------------------
void BinTree::makeEmpty()
{
    makeEmpty(root);
}

// ------------------------------------MakeEmpty----------------------------------------------- 
// Description: recursively works through tree deleting nodes
//      resets root to NULL to make old tree recycleable
// -------------------------------------------------------------------------------------------------------------
void BinTree::makeEmpty(Node* sub)
{
    if(sub != NULL)
    {
        makeEmpty(sub->left);
        makeEmpty(sub->right);
        delete sub;
    }
    root = NULL;
}

// ------------------------------------isEmpty----------------------------------------------- 
// Description: tests to see whether the root is allocated
//      if not returns false
// -------------------------------------------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
    if(root == NULL)
        return true;
    else return false;
}


// ------------------------------------Insert----------------------------------------------- 
// Description: Iteratively fills a tree
// -------------------------------------------------------------------------------------------------------------
bool BinTree::insert(NodeData* str) 
{
    Node *node = new Node;
    node->data = str;
    node->left = node->right = NULL;

    if(root == NULL)
        root = node;
    else
    {
        Node *pointer = root;
        while(true)
        {
            if(*str < *pointer->data)
            {
                if(pointer->left == NULL)
                {
                    pointer->left = node;
                    return true;
                }
                else pointer = pointer->left;
            }
            else if(*str > *pointer->data)
            {
                if(pointer->right == NULL)
                {
                    pointer->right = node;
                    return true;
                }
                else pointer = pointer->right;
            }
            else
                {
                    delete node;
                    return false;
                }
        }
    }

    return true;
}

// ------------------------------------Equals Operator----------------------------------------------- 
// Description: calls recursive compare function
// -------------------------------------------------------------------------------------------------------------
bool BinTree::operator==(const BinTree &rhs) const
{
    return compare(root, rhs.root);
}

// ------------------------------------Not Equal Operator----------------------------------------------- 
// Description: calls equality operator
//      returns false if equality operator returns true
// -------------------------------------------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree &rhs) const
{
    if(*this == rhs)
        return false;
    else return true;
}

// ------------------------------------compare----------------------------------------------- 
// Description: recursively compares two trees for equivalent shape and content
// -------------------------------------------------------------------------------------------------------------
bool BinTree::compare(const Node *john, const Node *zoeller) const 
{
    if(john == zoeller)
        return true;

    if(!john || !zoeller)
        return false;

    return ((john->data == zoeller->data) 
        && compare (john->left,  zoeller->left ) 
        && compare (john->right, zoeller->right));
}

// ------------------------------------Retreive----------------------------------------------- 
// Description: sets NodeData *p to the value of the desired leaf if it exists
//  calls recursive retr to set pointer
//      if it does not exist, returns false and pointer is NULL
// -------------------------------------------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData &key, NodeData* &p) const
{
    Node *node = this->root;
    Node *pointer = retr(key, node);

    if(pointer != NULL)
        p = pointer->data;
    else return false;

    return true;
}

// ------------------------------------retr----------------------------------------------- 
// Description: recursively finds a given leaf and sets sub to that leaf
// -------------------------------------------------------------------------------------------------------------
BinTree::Node *BinTree::retr(const NodeData &key, Node *sub) const
{
    if(sub == NULL)
        return NULL;
    else if(key == *sub->data)
        return sub;
    else if(key < *sub->data)
        return retr(key, sub->left);
    else
        return retr(key, sub->right);
}

// ------------------------------------getLeafCount----------------------------------------------- 
// Description: calls recursive leaf helper
// -------------------------------------------------------------------------------------------------------------
int BinTree::getLeafCount() const
{
    if(isEmpty()) return 0;
    return leafHelper(root);
}

// ------------------------------------leafHelper----------------------------------------------- 
// Description: recursively finds the total amount of leaves
// -------------------------------------------------------------------------------------------------------------
int BinTree::leafHelper(Node* sub) const
{
    if(sub == NULL)
        return 0;
    else if(sub->left == NULL && sub->right == NULL)
        return 1;
    return leafHelper(sub->left) + leafHelper(sub->right);
}

// ------------------------------------getHeight----------------------------------------------- 
// Description: sets a Node pointer to the calling objects root. 
//      sets another node pointer to the value of the recursive call to retr
//          uses that result to call recursive getH function
// -------------------------------------------------------------------------------------------------------------
int BinTree::getHeight (const NodeData &key) const
{
    Node *node = this->root;
    Node *pointer = retr(key, node);

    return getH(pointer);
}

// ------------------------------------getH----------------------------------------------- 
// Description: recursively determines the height of a given leaf on the tree
//      returns the larger of the two branches
// -------------------------------------------------------------------------------------------------------------
int BinTree::getH(Node *sub) const
{    
    if(sub == NULL)
        return 0;

    int r =  getH(sub->right);
    int l = getH(sub->left);

    if(l > r)
        return l + 1;
    else return r + 1;
}

// ------------------------------------bstreeToArray----------------------------------------------- 
// Description:makes sure tree is not empty and then calls inOrderHelper to recursively
//      fill the array.  Empty's out the tree leaving it with a NULL root
// -------------------------------------------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* arr[])
{
    int i = 0;

    if(this->root != NULL)
        inorderHelper(arr, i, this->root);

    makeEmpty(this->root);
}

// ------------------------------------inorderHelper----------------------------------------------- 
// Description: recursively fills the array with the contents of the tree inorder
// -------------------------------------------------------------------------------------------------------------
void BinTree::inorderHelper(NodeData*arr[], int &index, Node *node) const
{
    if(node->left != NULL)
        inorderHelper(arr, index, node->left);

    arr[index++] = node->data;

    if(node->right != NULL)
        inorderHelper(arr, index, node->right);
}

// ------------------------------------arrayToBSTree----------------------------------------------- 
// Description: finds the last non- NULL element of the array.  sets that element to last
//      calls recursive balanced build function with the arr, last, and zero
//          resets the array to all NULL once finished
// -------------------------------------------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* arr[]) 
{
    int last = 0;

    for(int i = 0; i < 99; i++)
        if(arr[i] == NULL)
        {
            last = i - 1;
            break;
        }

    root = balancedBuild(arr, 0, last);

    for(int i = 0; i < 100; i++)
        arr[i] = NULL;
}

// ------------------------------------balanced build----------------------------------------------- 
// Description: allocates new leafs recursively and fills left and right pointers
// -------------------------------------------------------------------------------------------------------------
BinTree::Node *BinTree::balancedBuild(NodeData* arr[], int first, int last) const
{
    if(first > last)
        return NULL;

    int newRoot = first + (last - first) / 2;
    Node *node = new Node;
    
    node->data = arr[newRoot];
    node->left = balancedBuild(arr, first, newRoot - 1);
    node->right = balancedBuild(arr, newRoot + 1, last);

    return node;
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const
{
    sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const
{
    if (current != NULL)
    {
        level++;
        sideways(current->right, level);

        for (int i = level; i >= 0; i--)         // indent for readability, 4 spaces per depth level
            cout << "    ";

        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
}
