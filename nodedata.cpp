// ------------------------------------------------ nodeData.cpp --------------------------------------------------
// John Zoeller, CSS 343 A
// Creation Date: 1/16/16
// Date of Last Modification: 3/14/16
// -------------------------------------------------------------------------------------------------------------------- 
// Purpose - Implementation file for nodeData.h
// -------------------------------------------------------------------------------------------------------------------- 
// Notes on specifications, special algorithms, and assumptions
//      -modified to include stock of a movie
// --------------------------------------------------------------------------------------------------------------------
#include "nodedata.h"

//------------------- constructors/destructor  -------------------------------
NodeData::NodeData() 
{ 
    data = ""; 
    inStock = 0;
}

// ------------------------------------Overloaded Ostream----------------------------------------------- 
// Description: calls display help, returns ostream out
// -------------------------------------------------------------------------------------------------------------
NodeData::NodeData(const string& str, int sto)
{
    data = str;
    inStock = sto;
}

NodeData::NodeData(const NodeData& nd) 
{ 
    data = nd.data;
    inStock = nd.inStock; 
}

NodeData::NodeData(const string& s) 
{ 
    data = s;   
    inStock = 0;
} 

NodeData::~NodeData() { }

void NodeData::setStock(int newStock)
{
    inStock = newStock;
}

int NodeData::getStock()
{
    return inStock;
}
//------------------------- operator= ----------------------------------------
NodeData& NodeData::operator=(const NodeData& rhs) 
{
    if (this != &rhs) 
    {
        data = rhs.data;
        inStock = rhs.inStock;
    }
    return *this;
}

//------------------------- operator==,!= ------------------------------------
bool NodeData::operator==(const NodeData& rhs) const {
	return data == rhs.data;
}

bool NodeData::operator!=(const NodeData& rhs) const {
	return data != rhs.data;
}

//------------------------ operator<,>,<=,>= ---------------------------------
bool NodeData::operator<(const NodeData& rhs) const {
	return data < rhs.data;
}

bool NodeData::operator>(const NodeData& rhs) const {
	return data > rhs.data;
}

bool NodeData::operator<=(const NodeData& rhs) const {
	return data <= rhs.data;
}

bool NodeData::operator>=(const NodeData& rhs) const {
	return data >= rhs.data;
}

//------------------------------ setData -------------------------------------
// returns true if the data is set, false when bad data, i.e., is eof

bool NodeData::setData(istream& infile) {
	getline(infile, data);
	return !infile.eof();       // eof function is true when eof char is read
}

//-------------------------- operator<< --------------------------------------
ostream& operator<<(ostream& output, const NodeData& nd) {
	output << nd.data << " - In Stock : " << nd.inStock;
	return output;
}
