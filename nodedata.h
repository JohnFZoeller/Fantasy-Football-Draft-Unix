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
        int ran;
        string fir, las, pos, squ;
        bool taken;

    public:
        NodeData();
        ~NodeData();
        NodeData(const NodeData &);
        NodeData(const int, const string&, const string&, const string&, const string&);
        NodeData(const int);

        NodeData& operator=(const NodeData &);

        bool setData(istream&);
        bool isTaken();

        bool operator==(const NodeData &) const;
        bool operator!=(const NodeData &) const;
        bool operator<(const NodeData &) const;
        bool operator>(const NodeData &) const;
        bool operator<=(const NodeData &) const;
        bool operator>=(const NodeData &) const;
};

#endif
