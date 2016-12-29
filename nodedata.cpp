#include "nodedata.h"

//------------------- constructors/destructor  -------------------------------
NodeData::NodeData() { 
    ran = 0;
    fir = "      ";
    las = "        ";
    pos = "na";
    squ = "";
    taken = false;
}

NodeData::NodeData(const NodeData& nd) { 
    ran = nd.ran;
    fir = nd.fir;
    las = nd.las;
    pos = nd.pos;
    squ = nd.squ;
    taken = nd.taken;
}

NodeData::NodeData(const int r, const string& f, const string& l, const string& s, const string& p){
	ran = r; //rank
	fir = f; //first name
	las = l; //last name
	squ = s; //nfl team
	pos = p; //position
    taken = false;
}

NodeData::NodeData(const int rank){
    ran = rank;
    fir = "";
    las = "";
    pos = "";
    squ = "";
    taken = false;
}

NodeData::~NodeData() { }
//--------------------end constructors---------------------------

//------------------------- operators ----------------------------------------
NodeData& NodeData::operator=(const NodeData& rhs) {
    if (this != &rhs) 
    {
        ran = rhs.ran;
        pos = rhs.pos;
        squ = rhs.squ;
        fir = rhs.fir;
        las = rhs.las;
        taken = rhs.taken;
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

bool NodeData::getTaken(){
    return taken;
}

void NodeData::setTaken(bool set){
    taken = set;
}

char NodeData::getPos(){
    return pos[0];
}
//-------------------------- operator<< --------------------------------------
ostream& operator<<(ostream& output, const NodeData& nd) {
	output << "#" << nd.ran << " " << nd.pos << " " + nd.fir 
            + " " + nd.las + " " + nd.squ << endl;
	return output;
}
