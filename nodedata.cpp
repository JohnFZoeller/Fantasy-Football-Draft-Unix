#include "nodedata.h"

//------------------- constructors/destructor  -------------------------------
NodeData::NodeData() 
{ 
    ran = 0;
    fir = las = pos = squ = "";
}

NodeData::NodeData(const NodeData& nd) 
{ 
    ran = nd.ran;
    fir = nd.fir;
    las = nd.las;
    pos = nd.pos;
    squ = nd.squ;
}

NodeData::NodeData(const int r, const string& f, const string& l, const string& s, const string& p){
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
	getline(infile, las);
	return !infile.eof();       // eof function is true when eof char is read
}

//-------------------------- operator<< --------------------------------------
ostream& operator<<(ostream& output, const NodeData& nd) {
	output << nd.fir << " " << nd.las << ". # " << nd.ran
	<< " : " << nd.squ << endl;
	return output;
}
