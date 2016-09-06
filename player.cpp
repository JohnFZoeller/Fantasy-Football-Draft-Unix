#include "player.h"

Player::Player(){
	posit = squad = first = last = "";
	rank = 0;
}

NodeData* Player::makeFromStream(istream& in){
	getline(in, posit, ' ');
	in >> rank;
	in.get();	
	getline(in, squad, ' ');
	getline(in, first, ' ');
	getline(in, last, '\n');

	NodeData* john = new NodeData(rank, first, last, squad, posit);
    return john;
}