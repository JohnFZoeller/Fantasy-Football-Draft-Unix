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

	cout << "position = " << posit << " rank = " << rank << " squad = " << squad << " first = " 
	<< first << " last = " << last << "  " << endl;

	NodeData* john = new NodeData(rank, first, last, squad, posit);
    return john;
}