// ------------------------------------------------ nodeData.h ------------------------------------------------------- -
// John Zoeller, CSS 343 A
// Creation Date: 1/16/16
// Date of Last Modification: 3/14/16
// -------------------------------------------------------------------------------------------------------------------- 
// Purpose - Outline nodeData class
// -------------------------------------------------------------------------------------------------------------------- 
// Notes on specifications, special algorithms, and assumptions:
//
// --------------------------------------------------------------------------------------------------------------------
#ifndef NODEDATA_H
#define NODEDATA_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class NodeData 
{
    friend ostream & operator<<(ostream &, const NodeData &);

    private:
        string data;
        int inStock;

    public:
        NodeData();
        ~NodeData();
        NodeData(const string &);
        NodeData(const string&, int);
        NodeData(const NodeData &);
        NodeData& operator=(const NodeData &);


        bool setData(istream&);
        int getStock();
        void setStock(int);

        bool operator==(const NodeData &) const;
        bool operator!=(const NodeData &) const;
        bool operator<(const NodeData &) const;
        bool operator>(const NodeData &) const;
        bool operator<=(const NodeData &) const;
        bool operator>=(const NodeData &) const;
};

#endif
