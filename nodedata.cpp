#include "nodedata.h"

//------------------- constructors/destructor  -------------------------------
NodeData::NodeData() 
{ 
    data = ""; 
    inStock = 0;

    ran = 0;
    fir = las = pos = squ = "";
}

NodeData::NodeData(const string& str, int sto)
{
    data = str;
    inStock = sto;

    ran = 0;
    fir = las = pos = squ = "";  
}

NodeData::NodeData(const NodeData& nd) 
{ 
    data = nd.data;
    inStock = nd.inStock; 

    ran = nd.ran;
    fir = nd.fir;
    las = nd.las;
    pos = nd.pos;
    squ = nd.squ;
}

NodeData::NodeData(const string& s) 
{ 
    data = s;   
    inStock = 0;

    ran = 0;
    fir = las = pos = squ = "";
} 

NodeData::NodeData(const int r, const string& f, const string& l, const string& s, const string& p){
	data = "";
	inStock = 0;

	ran = r; //rank
	fir = f; //first name
	las = l; //last name
	squ = s; //nfl team
	pos = p; //position
}

NodeData::~NodeData() { }
//--------------------end constructors---------------------------

//------------------------- operators ----------------------------------------
NodeData& NodeData::operator=(const NodeData& rhs) 
{
    if (this != &rhs) 
    {
        data = rhs.data;
        inStock = rhs.inStock;

        ran = rhs.ran;
        pos = rhs.pos;
        squ = rhs.squ;
        fir = rhs.fir;
        las = rhs.las;
    }
    return *this;
}

//------------------------- operator==,!= ------------------------------------
bool NodeData::operator==(const NodeData& rhs) const {
	return ran == rhs.ran;
}

bool NodeData::operator!=(const NodeData& rhs) const {
	return ran != rhs.ran;
}

//------------------------ operator<,>,<=,>= ---------------------------------
bool NodeData::operator<(const NodeData& rhs) const {
	return ran < rhs.ran;
}

bool NodeData::operator>(const NodeData& rhs) const {
	return ran > rhs.ran;
}

bool NodeData::operator<=(const NodeData& rhs) const {
	return ran <= rhs.ran;
}

bool NodeData::operator>=(const NodeData& rhs) const {
	return ran >= rhs.ran;
}

//-------------------------------end operators------------------
//------------------------------ setData -------------------------------------
// returns true if the data is set, false when bad data, i.e., is eof

bool NodeData::setData(istream& infile) {
	getline(infile, data);
	return !infile.eof();       // eof function is true when eof char is read
}

//-------------------------- operator<< --------------------------------------
ostream& operator<<(ostream& output, const NodeData& nd) {
	output << nd.fir << " " << nd.las << ". # " << nd.ran
	<< " Team: " << nd.squ << endl;
	return output;
}
